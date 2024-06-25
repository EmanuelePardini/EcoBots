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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Quantity;
	
	void Init(int InitialQuantity, TSubclassOf<UInventoryItem> SlotType);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UInventoryItem* GetInventoryItem() const {return InventoryItem;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSubclassOf<UInventoryItem> GetItemType() const {return Type;}
};
