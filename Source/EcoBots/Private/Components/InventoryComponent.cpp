// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Characters/EcoBotCharacter.h"
#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::StartEventListening(UInventorySlot* Slot)
{
	Slot->OnSlotUse.AddDynamic(this, &UInventoryComponent::UseItem);
	Slot->OnSlotDrop.AddDynamic(this, &UInventoryComponent::DropItem);
}

bool UInventoryComponent::AddItem(AItem* Item)
{
	bool Contained = InventoryMap.Contains(Item->GetItemData());
	
	//If the Item is already contained and stackable then is to stack
	if(Contained)
	{
		InventoryMap[Item->GetItemData()]->Quantity += Item->Quantity;
	}
	else
	{
		//Check if there's space in the inventory
		if(InventoryArray.Num() >= InventoryLength) return false;

		//add a slot and Insert Item in a new slot
		UInventorySlot* NewSlot = NewObject<UInventorySlot>();
		NewSlot->Init(Item->Quantity, Item->GetItemData());
		StartEventListening(NewSlot);
		InventoryMap.Add(Item->GetItemData(), NewSlot);
		InventoryArray.Add(NewSlot);
	}

	//Destroy InScene Item
	Item->Destroy();
	OnInventoryChanged.Broadcast(InventoryArray);
	return true;
}

void UInventoryComponent::UseItem(UInventoryItem* Item, int Quantity)
{
	//If the Item is not usable in Inventory it will not be used: Check BP_InventorySlotWidget
	
	//If is not a character then can't use the Item
	AEcoBotCharacter* EcoBotCharacter = Cast<AEcoBotCharacter>(GetOwner());
	if(!EcoBotCharacter) return;
	
	//If the inventory has the item required
	TSubclassOf<UInventoryItem> ItemData = Item->GetClass();
	bool Contained = InventoryMap.Contains(ItemData);
	if (!Contained) return;
	
	//If you have enough item of the type specified
	bool IsEnough = InventoryMap[ItemData]->Quantity >= Quantity ? true : false;
	if (!IsEnough) return;

	//Use the Item
	for(int i = 0; i < Quantity; i++)
	{
		Item->UseInventoryItem(EcoBotCharacter);
	}
	
	//then subtract it to your inventory
	InventoryMap[ItemData]->Quantity -= Quantity;
		
	if(InventoryMap[ItemData]->Quantity <= 0) //if the remaining quantity is 0 remove the slot
	{
		UInventorySlot* Slot = InventoryMap.FindRef(ItemData);
		InventoryMap.Remove(ItemData);
		InventoryArray.Remove(Slot);
	}

	OnInventoryChanged.Broadcast(InventoryArray);
}

void UInventoryComponent::UseItemByClass(TSubclassOf<UInventoryItem> ItemData, int Quantity)
{
	if (!ItemData) return;
	
	if (UInventorySlot* Slot = InventoryMap.FindRef(ItemData))
		UseItem(Slot->GetInventoryItem(), Quantity);
}

bool UInventoryComponent::MoveItem(UInventorySlot* Slot)
{
	bool Contained = InventoryMap.Contains(Slot->GetItemType());

	if(Contained)
	{
		InventoryMap[Slot->GetItemType()]->Quantity += Slot->Quantity;
	}
	else
	{
		//Check if there's space in the inventory
		if(InventoryArray.Num() >= InventoryLength) return false;

		//add a slot and Insert Item in a new slot
		UInventorySlot* NewSlot = NewObject<UInventorySlot>();
		NewSlot->Init(Slot->Quantity, Slot->GetItemType());
		InventoryMap.Add(Slot->GetItemType(), NewSlot);
		InventoryArray.Add(NewSlot);
		StartEventListening(NewSlot);
	}

	OnInventoryChanged.Broadcast(InventoryArray);
	return true;
}

bool UInventoryComponent::MoveAll(UInventoryComponent* NewInventory)
{
	for (UInventorySlot* Slot : InventoryArray)
	{
		//If the new inventory is full stop transfer
		if(NewInventory->InventoryArray.Num() >= NewInventory->InventoryLength) return false;
		//if not transfer the Slots
		NewInventory->MoveItem(Slot);
	}
	
	InventoryMap.Empty();
	InventoryArray.Empty();

	OnInventoryChanged.Broadcast(InventoryArray);
	return true;
}


void UInventoryComponent::DropItem(UInventorySlot* Slot, int DropQuantity)
{
	// If Inventory is empty or the item is not in the inventory, do nothing
	if (InventoryMap.IsEmpty() || !InventoryMap.Contains(Slot->GetInventoryItem()->GetClass())) return;

	// If the item slot is not found or DropQuantity is less than or equal to zero, do nothing
	if (!Slot || Slot->Quantity <= 0 || DropQuantity <= 0) return;

	// Get the information to spawn the item in scene
	const FVector Position = FVector(GetOwner()->GetActorLocation().X + 100, GetOwner()->GetActorLocation().Y, GetOwner()->GetActorLocation().Z);
	const FRotator Rotation = GetOwner()->GetActorRotation();
	TSubclassOf<AInteractable> Interactable = Slot->GetInventoryItem()->GetItemToSpawn();

	// Spawn the actor and cast it to item
	AItem* SpawnedItem = Cast<AItem>(GetWorld()->SpawnActor(Interactable, &Position, &Rotation));

	// Calculate the actual quantity to drop
	DropQuantity = FMath::Min(DropQuantity, Slot->Quantity);
	SpawnedItem->Quantity = DropQuantity;

	// Adjust the quantity in the inventory
	if (DropQuantity >= Slot->Quantity)
	{
		// If dropping all, remove the slot from inventory
		InventoryMap.Remove(Slot->GetInventoryItem()->GetClass());
		InventoryArray.Remove(Slot);
	}
	else
	{
		// Otherwise, just reduce the quantity
		Slot->Quantity -= DropQuantity;
	}

	// Notify about the inventory change
	OnInventoryChanged.Broadcast(InventoryArray);
}


int UInventoryComponent::GetItemCount(TSubclassOf<UInventoryItem> ItemToCount)
{
	if (UInventorySlot* Slot = InventoryMap.FindRef(ItemToCount))
	{
		return Slot->Quantity;
	}
	
	return 0; //If not found
}

TMap<TSubclassOf<UInventoryItem>, float> UInventoryComponent::SaveInventory()
{
	//Declare the map needed for saving data
	TMap<TSubclassOf<UInventoryItem>, float> InventoryInfo;
	
	for(int i = 0; i < InventoryArray.Num(); i++)
	{
		if(InventoryArray[i])
		{
			//Add item to the map
			InventoryInfo.Add(InventoryArray[i]->GetItemType(), InventoryArray[i]->Quantity);
		}
	}
	//Return the map
	return InventoryInfo;
}

void UInventoryComponent::LoadInventory(TMap<TSubclassOf<UInventoryItem>, float> Item)
{
	// Iterate through the passed map to load items into the inventory
	for (const TPair<TSubclassOf<UInventoryItem>, float>& ItemData : Item)
	{
		// Create a new inventory slot
		UInventorySlot* NewSlot = NewObject<UInventorySlot>();
        
		// Initialize the new slot with the item type and quantity
		NewSlot->Init(ItemData.Value, ItemData.Key);
        
		// Add the new slot to the inventory map and array
		InventoryMap.Add(ItemData.Key, NewSlot);
		InventoryArray.Add(NewSlot);
		StartEventListening(NewSlot);
	}
	OnInventoryChanged.Broadcast(InventoryArray);
}