// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Interactables/Interactable.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API AItem : public AInteractable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	uint8 Quantity = 1;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
	TSubclassOf<UInventoryItem> ItemData = UInventoryItem::StaticClass();

public:
	FORCEINLINE TSubclassOf<UInventoryItem> GetItemData() const {return ItemData;}
	virtual void Tick(float DeltaSeconds) override;
	virtual void Interact(AEcoBotCharacter* InteractingChar) override;
};
