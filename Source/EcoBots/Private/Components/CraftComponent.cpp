// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CraftComponent.h"
#include "Characters/EcoBotCharacter.h"
#include "Craftables/CraftablePreview.h"

// Sets default values for this component's properties
UCraftComponent::UCraftComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCraftComponent::BeginPlay()
{
	Super::BeginPlay();

	AEcoBotCharacter* EcoBotCharacter = Cast<AEcoBotCharacter>(GetOwner());
	if(EcoBotCharacter) InventoryReference = EcoBotCharacter->GetInventory();
	
}


// Called every frame
void UCraftComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCraftComponent::CraftPreview(int32 RecipeIndex)
{
	if(!InventoryReference) return;
	
	FRecipeStruct RecipeStruct = CraftRecipes[RecipeIndex]->RecipeStruct;
	
	 // Check if the recipe is unlocked
    if (!RecipeStruct.UnlockCraftable.Unlocked)
    {
        // Check if we have the materials to unlock the recipe
        int UnlockMaterialCount = InventoryReference->GetItemCount(RecipeStruct.UnlockCraftable.UnlockMaterial);
        if (UnlockMaterialCount < RecipeStruct.UnlockCraftable.UnlockCost) return;
    	
    	// Unlock the recipe
        RecipeStruct.UnlockCraftable.Unlocked = true;  

    }

    // Check if we have all the materials needed to craft
    bool bCanCraft = true;
    for (const FCraftMaterialCost& MaterialCost : RecipeStruct.RequiredMaterials)
    {
        int MaterialCount = InventoryReference->GetItemCount(MaterialCost.RequiredMaterial);
        if (MaterialCount < MaterialCost.Quantity)
        {
            bCanCraft = false;
            break;
        }
    }

    if (bCanCraft)
    {
        // Spawn the preview
        UWorld* World = GetWorld();
        if (World && RecipeStruct.PreviewToSpawn)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = GetOwner();
            AEcoBotCharacter* EcoBotCharacter = Cast<AEcoBotCharacter>(GetOwner());
            FVector SpawnLoc = EcoBotCharacter->GetActorLocation();
            FRotator SpawnRot = EcoBotCharacter->GetActorRotation();

        	if(PossessedPreview) PossessedPreview->Destroy();
            PossessedPreview = World->SpawnActor<ACraftablePreview>(RecipeStruct.PreviewToSpawn, SpawnLoc, SpawnRot, SpawnParams);
            if (PossessedPreview)
            {
                PossessedPreview->SetEcoBotReference(EcoBotCharacter);
                PossessedPreview->SetCraftRecipe(RecipeStruct.RequiredMaterials);
            }
        }
    }
}