#pragma once
#include "CoreMinimal.h"
#include "Items/InventoryItem.h"
#include "CraftRecipe.generated.h"
class ACraftable;

USTRUCT(BlueprintType, Blueprintable)
struct FCraftMaterialCost
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Cost")
	TSubclassOf<UInventoryItem> RequiredMaterial;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Cost")
	int Quantity; 
};

USTRUCT(BlueprintType, Blueprintable)
struct FCraftRecipe
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TArray<FCraftMaterialCost> RequiredMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	bool Unlocked = false;
};
//TODO: Update Recipe