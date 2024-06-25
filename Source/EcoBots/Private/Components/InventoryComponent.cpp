// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
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

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
		InventoryMap.Add(Item->GetItemData(), NewSlot);
		InventoryArray.Add(NewSlot);
	}

	//Destroy InScene Item
	Item->Destroy();

	OnInventoryChanged.Broadcast(InventoryArray);
	return true;
}

bool UInventoryComponent::UseItem(TSubclassOf<UInventoryItem> ItemData, int Quantity)
{
	//If the inventory has the item required
	bool Contained = InventoryMap.Contains(ItemData);
	if (!Contained) return false;
	
	//If you have enough item of the type specified
	bool IsEnough = InventoryMap[ItemData]->Quantity >= Quantity ? true : false;
	if (!IsEnough) return false;
	
	//then subtract it to your inventory
	InventoryMap[ItemData]->Quantity -= Quantity;
		
	if(InventoryMap[ItemData]->Quantity <= 0) //if the remaining quantity is 0 remove the slot
		{
		UInventorySlot* Slot = InventoryMap.FindRef(ItemData);
		InventoryMap.Remove(ItemData);
		InventoryArray.Remove(Slot);
		}

	OnInventoryChanged.Broadcast(InventoryArray);
	return true;
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

bool UInventoryComponent::DropItem(bool RemoveHalf)
{
	//If Inventory is Empty do nothing
	if(InventoryMap.IsEmpty()) return false;

	//Find the last item of the inventory
	UInventorySlot* LastSlot = InventoryArray.Last();
		
	//Get the information to spawn the Item InScene
	const FVector Position = FVector(GetOwner()->GetActorLocation().X+100,GetOwner()->GetActorLocation().Y,GetOwner()->GetActorLocation().Z);
	const FRotator Rotation = GetOwner()->GetActorRotation();
	TSubclassOf<AInteractable> Interactable = LastSlot->GetInventoryItem()->GetItemToSpawn();
	
	
	//Spawn the Actor and cast it to Item
	AItem* SpawnedItem = Cast<AItem>(GetWorld()->SpawnActor(Interactable, &Position, &Rotation));
	
	//Remove it from the collections if is Total or if the quantity is one or less
	if(!RemoveHalf || LastSlot->Quantity <= 1)
	{
		//Reassign to the Item his previous Quantity
		SpawnedItem->Quantity = LastSlot->Quantity;
		
		InventoryMap.Remove(SpawnedItem->GetItemData());
		InventoryArray.Remove(LastSlot);
	}
	else //else if is half spawn the half quantity of the Item and keep the other half
	{
		float ReductionFactor = 0.5f;

		if (LastSlot->Quantity % 2 == 1)
		{
			// If the quantity is odd, spawn the floor(Quantity / 2) items and keep the ceiling(Quantity / 2) items
			int32 SpawnedQuantity = FMath::FloorToInt(LastSlot->Quantity * ReductionFactor);
			SpawnedItem->Quantity = SpawnedQuantity;

			LastSlot->Quantity -= SpawnedQuantity;
		}
		else
		{
			// If the quantity is even, spawn half and keep half
			SpawnedItem->Quantity = FMath::FloorToInt(LastSlot->Quantity * ReductionFactor);
			LastSlot->Quantity *= ReductionFactor;
		}
	}

	OnInventoryChanged.Broadcast(InventoryArray);
	return true;
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
	}
}

