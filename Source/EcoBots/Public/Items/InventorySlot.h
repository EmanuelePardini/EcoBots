// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ECOBOTS_API UInventorySlot : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	UInventoryItem* InventoryItem;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UInventoryItem> Type;

public:
	UPROPERTY(VisibleAnywhere)
	int Quantity;
	
	void Init(int InitialQuantity, TSubclassOf<UInventoryItem> SlotType);
	FORCEINLINE UInventoryItem* GetInventoryItem() const {return InventoryItem;}
	FORCEINLINE TSubclassOf<UInventoryItem> GetItemType() const {return Type;}
};
