#pragma once
#include "CoreMinimal.h"
#include "Items/InventoryItem.h"
#include "RecipeStruct.generated.h"
class ACraftablePreview;

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
struct FUnlockCraftable
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	bool Unlocked = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TSubclassOf<UInventoryItem> UnlockMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	int UnlockCost;
};

USTRUCT(BlueprintType)
struct FRecipeStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Crafting")
	FString CraftableName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Crafting")
	UTexture2D* CraftableIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TSubclassOf<ACraftablePreview> PreviewToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TArray<FCraftMaterialCost> RequiredMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	FUnlockCraftable UnlockCraftable;

};
