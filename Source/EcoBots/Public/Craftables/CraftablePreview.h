// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RecipeStruct.h"
#include "Craftables/Craftable.h"
#include "CraftablePreview.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API ACraftablePreview : public ACraftable
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEcoBotCharacter* EcoBotReference;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCraftMaterialCost> NeededMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craftable")
	TSubclassOf<ACraftable> CraftableToSpawn;

public:
	virtual void Tick(float DeltaSeconds) override;
	void ManagePreview();
	void SetCraftRecipe(TArray<FCraftMaterialCost> MaterialCosts);
	void SetEcoBotReference(AEcoBotCharacter* NewEcoBot);
	virtual void Interact(AEcoBotCharacter* InteractingChar) override;
	void SpawnCraft();
	
};
