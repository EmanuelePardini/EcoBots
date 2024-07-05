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
	InitRecipes();
}

void UCraftComponent::InitRecipes()
{
	// Clear the CraftRecipes array to ensure no existing data is present
	CraftRecipes.Empty();

	// Loop through all classes in CraftRecipesClasses
	for (TSubclassOf<UCraftRecipe> RecipeClass : CraftRecipesClasses)
	{
		// Check if the class is valid
		if (RecipeClass)
		{
			// Create a new instance of the UCraftRecipe object
			UCraftRecipe* NewRecipe = NewObject<UCraftRecipe>(this, RecipeClass);
            
			// Check if the new instance is valid
			if (NewRecipe)
			{
				// Add the new instance to the CraftRecipes array
				CraftRecipes.Add(NewRecipe);
				NewRecipe->OnRecipeUse.AddDynamic(this, &UCraftComponent::CraftPreview);
			}
		}
	}

	//Clear the Array with classes
	CraftRecipesClasses.Empty();
}


// Called every frame
void UCraftComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCraftComponent::CraftPreview(UCraftRecipe* CraftRecipeRef)
{
	if(!InventoryReference|| !CraftRecipeRef) return;

	int32 RecipeIndex = CraftRecipes.Find(CraftRecipeRef);
	
	FRecipeStruct& RecipeStruct = CraftRecipes[RecipeIndex]->RecipeStruct;
	
	 // Check if the recipe is unlocked
    if (!RecipeStruct.UnlockCraftable.Unlocked)
    {
        // Check if we have the materials to unlock the recipe
        int UnlockMaterialCount = InventoryReference->GetItemCount(RecipeStruct.UnlockCraftable.UnlockMaterial);
        if (UnlockMaterialCount < RecipeStruct.UnlockCraftable.UnlockCost) return;
    	
    	InventoryReference->UseItemByClass(RecipeStruct.UnlockCraftable.UnlockMaterial, RecipeStruct.UnlockCraftable.UnlockCost);
    	
    	// Unlock the recipe
        RecipeStruct.UnlockCraftable.Unlocked = true;
    	OnCraftChanged.Broadcast(CraftRecipes);
    	return;
    }
	
    // Spawn the preview
    UWorld* World = GetWorld();
    if (World && RecipeStruct.PreviewToSpawn)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = GetOwner();
        AEcoBotCharacter* EcoBotCharacter = Cast<AEcoBotCharacter>(GetOwner());
        FVector SpawnLoc = EcoBotCharacter->GetActorLocation();
        FRotator SpawnRot = EcoBotCharacter->GetActorRotation();
    	
        ACraftablePreview* NewPreview = World->SpawnActor<ACraftablePreview>(RecipeStruct.PreviewToSpawn, SpawnLoc, SpawnRot, SpawnParams);
    	
    	if(InUsePreview) InUsePreview->IsPlacing = false;
    	InUsePreview = NewPreview;

    	
        if (InUsePreview)
        {
            InUsePreview->SetEcoBotReference(EcoBotCharacter);
            InUsePreview->SetCraftRecipe(RecipeStruct.RequiredMaterials);
        }
    }
	OnCraftChanged.Broadcast(CraftRecipes);
}
	


TMap<TSubclassOf<UCraftRecipe>, bool> UCraftComponent::SaveCraftRecipes()
{
	TMap<TSubclassOf<UCraftRecipe>, bool> RecipesUnlockStatus;

	if(!CraftRecipes.IsEmpty())
	{
		for (auto CraftRecipe : CraftRecipes)
		{
			RecipesUnlockStatus.Add(CraftRecipe->GetClass(), CraftRecipe->RecipeStruct.UnlockCraftable.Unlocked);
		}	
	}
	
	return  RecipesUnlockStatus;
}

void UCraftComponent::LoadCraftRecipes(TMap<TSubclassOf<UCraftRecipe>, bool> RecipesStatus)
{
	for (UCraftRecipe* Recipe : CraftRecipes)
	{
		if (Recipe)
		{
			TSubclassOf<UCraftRecipe> RecipeClass = Recipe->GetClass();
			if (RecipesStatus.Contains(RecipeClass))
			{
				bool bIsUnlocked = RecipesStatus[RecipeClass] ? true : false;
				Recipe->RecipeStruct.UnlockCraftable.Unlocked = bIsUnlocked;
			}
		}
	}
}
