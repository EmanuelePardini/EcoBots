// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InventoryComponent.h"
#include "Items/InventoryItem.h"
#include "Items/InventorySlot.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EcoBotDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UEcoBotDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UMaterialInterface*> EcoBotMaterials = {nullptr, nullptr};
	UPROPERTY(VisibleAnywhere)
	FTransform EcoBotTransform;
	UPROPERTY(VisibleAnywhere)
	float Health;
	UPROPERTY(VisibleAnywhere)
	float Hunger;
	UPROPERTY(VisibleAnywhere)
	float Thirst;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInventoryComponent* Inventory;

public:
	UFUNCTION(BlueprintCallable)
	TArray<UMaterialInterface*> GetEcoBotMaterials();
	UFUNCTION(BlueprintCallable)
	void SetEcoBotMaterials(UMaterialInterface* Body = nullptr, UMaterialInterface* Face = nullptr);
	UFUNCTION(BlueprintCallable)
	FTransform GetEcoBotTransform();
	UFUNCTION(BlueprintCallable)
	void SetEcoBotTransform(FTransform NewTransform);
	UFUNCTION(BlueprintCallable)
	TArray<float> GetEcoBotStats();
	UFUNCTION(BlueprintCallable)
	void SetEcoBotStats(float NewHealth, float NewHunger, float NewThirst);
	// UFUNCTION(BlueprintCallable)
	// UInventoryComponent* GetEcoBotInventory();
	// UFUNCTION(BlueprintCallable)
	// void SetEcoBotInventory(UInventoryComponent* NewInventory);

};
