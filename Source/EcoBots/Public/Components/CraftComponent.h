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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftChanged, const TArray<UCraftRecipe*>&, Recipes);
	FOnCraftChanged OnCraftChanged;

protected:
	// Sets default values for this component's properties
	UCraftComponent();
	UPROPERTY(EditAnywhere, Category = "Recipes")
	TArray<TSubclassOf<UCraftRecipe>> CraftRecipesClasses;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UCraftRecipe*> CraftRecipes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* InventoryReference;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ACraftablePreview* InUsePreview = nullptr;


	// Called when the game starts
	virtual void BeginPlay() override;
	void InitRecipes();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UCraftRecipe*> GetRecipes() {return CraftRecipes;}
	UFUNCTION(BlueprintCallable)
	void CraftPreview(UCraftRecipe* CraftRecipeRef);
	UFUNCTION(BlueprintCallable)
	TMap<TSubclassOf<UCraftRecipe>, bool> SaveCraftRecipes();
	UFUNCTION(BlueprintCallable)
	void LoadCraftRecipes(TMap<TSubclassOf<UCraftRecipe>, bool> RecipesStatus);
};
