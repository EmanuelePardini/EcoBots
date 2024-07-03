// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Interactable.h"
#include "UObject/Class.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ECOBOTS_API UInventoryItem : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	UTexture2D* ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	FString ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	bool bIsInventoryUsable = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	TSubclassOf<AInteractable> ItemToSpawn;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetItemName() const {return ItemName;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsUsable() const {return bIsInventoryUsable;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetItemType() const {return ItemType;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetItemIcon() const {return ItemIcon;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TSubclassOf<AInteractable> GetItemToSpawn() const {return ItemToSpawn;}
	UFUNCTION(BlueprintCallable)
	void UseInventoryItem(AEcoBotCharacter* EcoBotCharacter);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUseInventoryItem(AEcoBotCharacter* EcoBotCharacter);
};
