// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RecipeStruct.h"
#include "Components/WidgetComponent.h"
#include "Craftables/Craftable.h"
#include "CraftablePreview.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API ACraftablePreview : public ACraftable
{
	GENERATED_BODY()
public:
	ACraftablePreview();
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	UStaticMeshComponent* PreviewMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UI")
	UWidgetComponent* ActionsWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEcoBotCharacter* EcoBotReference;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsPlacing = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCraftMaterialCost> NeededMaterials;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craftable")
	TSubclassOf<ACraftable> CraftableToSpawn;

	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;
	void UpdateWidgetRotation();
	void ManagePreviewPlacing();
	void SetCraftRecipe(TArray<FCraftMaterialCost> MaterialCosts);
	void SetEcoBotReference(AEcoBotCharacter* NewEcoBot);
	virtual void Interact(AEcoBotCharacter* InteractingChar) override;
	UFUNCTION(BlueprintCallable)
	void SpawnCraft();
	
};
