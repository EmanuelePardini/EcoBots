// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/InventoryItem.h"
#include "Items/InventorySlot.h"
#include "Items/Item.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryChanged, const TArray<UInventorySlot*>&, Slots);
	FOnInventoryChanged OnInventoryChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<UInventoryItem>, UInventorySlot*> InventoryMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UInventorySlot*> InventoryArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	int InventoryLength = 20;

	
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void StartEventListening(UInventorySlot* Slot);
	UFUNCTION(BlueprintCallable)
	bool AddItem(AItem* Item);
	UFUNCTION(BlueprintCallable)
	void UseItem(UInventoryItem* ItemData, int Quantity = 1);
	UFUNCTION(BlueprintCallable)
	void UseItemByClass(TSubclassOf<UInventoryItem> ItemData, int Quantity = 1);
	UFUNCTION(BlueprintCallable)
	bool MoveItem(UInventorySlot* Slot);
	UFUNCTION(BlueprintCallable)
	bool MoveAll(UInventoryComponent* NewInventory);
	UFUNCTION(BlueprintCallable)
	void DropItem(UInventorySlot* Slot, int DropQuantity);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UInventorySlot*> GetInventoryArray(){return InventoryArray;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UInventoryComponent* GetInventory(){return this;}
	UFUNCTION(BlueprintCallable)
	int GetItemCount(TSubclassOf<UInventoryItem> ItemToCount);
	UFUNCTION(BlueprintCallable)
	TMap<TSubclassOf<UInventoryItem>, float> SaveInventory();
	UFUNCTION(BlueprintCallable)
	void LoadInventory(TMap<TSubclassOf<UInventoryItem>, float> Item);
};
