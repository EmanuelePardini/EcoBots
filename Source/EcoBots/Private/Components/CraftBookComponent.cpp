// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Components\CraftBookComponent.h"

#include "Characters/EcoBotCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/InventoryComponent.h"

// Sets default values for this component's properties
UCraftBookComponent::UCraftBookComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UCraftBookComponent::BeginPlay()
{
    Super::BeginPlay();
    InitInventoryReference();
}

void UCraftBookComponent::InitInventoryReference()
{
    AEcoBotCharacter* EcoBot = Cast<AEcoBotCharacter>(GetOwner());

    if(!EcoBot) return;

    InventoryReference = EcoBot->GetInventory();
}

// Called every frame
void UCraftBookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

bool UCraftBookComponent::Craft(UCraftBookCraftable* Craftable)
{
    if (!InventoryReference) return false;

    if (!Craftable->CraftRecipe.Unlocked) return false;

    // Map to keep track of the required materials and their quantities
    TMap<TSubclassOf<UInventoryItem>, int32> RequiredMaterialsMap;

    // Populate the map with required materials
    for (const auto& Required : Craftable->CraftRecipe.RequiredMaterials)
    {
        RequiredMaterialsMap.Add(Required.RequiredMaterial, Required.Quantity);
    }

    // Check inventory for required materials
    for (const auto& InventorySlot : InventoryReference->GetInventoryArray())
    {
        TSubclassOf<UInventoryItem> ItemClass = InventorySlot->GetInventoryItem()->GetClass();

        if (RequiredMaterialsMap.Contains(ItemClass))
        {
            int32& RequiredQuantity = RequiredMaterialsMap[ItemClass];

            if (InventorySlot->Quantity >= RequiredQuantity)
            {
                RequiredQuantity = 0; // Found sufficient quantity, set to 0
            }
            else
            {
                RequiredQuantity -= InventorySlot->Quantity; // Subtract found quantity
            }
        }
    }

    // Check if all required materials are found in sufficient quantity
    for (const auto& Required : RequiredMaterialsMap)
    {
        if (Required.Value > 0)
        {
            return false; // Not enough materials
        }
    }

    // Remove materials from inventory
    for (auto& Required : Craftable->CraftRecipe.RequiredMaterials)
    {
        for (auto& InventorySlot : InventoryReference->GetInventoryArray())
        {
            if (InventorySlot->GetInventoryItem()->GetClass() == Required.RequiredMaterial)
            {
                if (InventorySlot->Quantity >= Required.Quantity)
                {
                    InventorySlot->Quantity -= Required.Quantity;
                    break; // Move to the next required material
                }
                else
                {
                    Required.Quantity -= InventorySlot->Quantity;
                    InventorySlot->Quantity = 0; // Remove everything from the current slot
                }
            }
        }
    }

    // Spawn the crafted item
    SpawnCraftable(Craftable->ItemToSpawn);

    return true;
}

void UCraftBookComponent::SpawnCraftable(TSubclassOf<AItem> ItemToSpawn)
{
    if (!ItemToSpawn) return;
    
    FVector SpawnLocation = GetOwner()->GetActorLocation();
    FRotator SpawnRotation = GetOwner()->GetActorRotation();

    GetWorld()->SpawnActor<AActor>(ItemToSpawn, SpawnLocation, SpawnRotation);
    //This will spawn an Item that can be added to the inventory, then Using it, it will spawn the craftable preview
}
