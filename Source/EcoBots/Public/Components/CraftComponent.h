// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "Craftables/CraftRecipe.h"
#include "CraftComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UCraftComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCraftComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipes")
	TArray<UCraftRecipe*> CraftRecipes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* InventoryReference;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACraftablePreview* PossessedPreview = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void CraftPreview(int32 RecipeIndex);
	UFUNCTION(BlueprintCallable)
	TMap<TSubclassOf<UCraftRecipe>, bool> SaveCraftRecipes();
	UFUNCTION(BlueprintCallable)
	void LoadCraftRecipes(TMap<TSubclassOf<UCraftRecipe>, bool> RecipesStatus);
};
