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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotUse, UInventoryItem*, InventoryItem, int, Qt);
	FOnSlotUse OnSlotUse;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotDrop, UInventorySlot*, InventorySlot, int, Qt);
	FOnSlotDrop OnSlotDrop;
	
	void Init(int InitialQuantity, TSubclassOf<UInventoryItem> SlotType);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UInventoryItem* GetInventoryItem() const {return InventoryItem;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSubclassOf<UInventoryItem> GetItemType() const {return Type;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void UseSlot(UInventoryItem* ToUseItem, int ToUseQt){OnSlotUse.Broadcast(ToUseItem, ToUseQt);}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void DropSlot(int ToUseQt){OnSlotDrop.Broadcast(this, ToUseQt);}
};
