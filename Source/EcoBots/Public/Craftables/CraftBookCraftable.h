// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CraftRecipe.h"
#include "UObject/NoExportTypes.h"
#include "CraftBookCraftable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ECOBOTS_API UCraftBookCraftable : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Craftable")
	FCraftRecipe CraftRecipe;
	
};
//TODO:Update CraftBookCraftable