// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CraftRecipe.h"
#include "CraftBookCraftable.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UCraftBookCraftable : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Craftable")
	FCraftRecipe CraftRecipe;
	
};
//TODO:Update CraftBookCraftable