// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Interactable.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ECOBOTS_API UInventoryItem : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Setup")
	FString ItemName;
	UPROPERTY(EditAnywhere, Category="Setup")
	UTexture2D* ItemIcon;
	UPROPERTY(EditAnywhere, Category="Setup")
	FString ItemType;
	UPROPERTY(EditAnywhere, Category="Setup")
	TSubclassOf<AInteractable> ItemToSpawn;

public:
	FORCEINLINE FString GetItemName() const {return ItemName;}
	FORCEINLINE FString GetItemType() const {return ItemType;}
	FORCEINLINE TSubclassOf<AInteractable> GetItemToSpawn() const {return ItemToSpawn;}
};
