// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RecipeStruct.h"
#include "CraftRecipe.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ECOBOTS_API UCraftRecipe : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe")
	FRecipeStruct RecipeStruct;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRecipeUse, UCraftRecipe*, CraftRecipe);
	FOnRecipeUse OnRecipeUse;
	
	UFUNCTION(BlueprintCallable)
	void UseRecipe();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUseRecipe();
};
