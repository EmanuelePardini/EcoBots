// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RecipeStruct.h"
#include "Engine/DataAsset.h"
#include "CraftRecipe.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UCraftRecipe : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recipe")
	FRecipeStruct RecipeStruct;
	
	
};
