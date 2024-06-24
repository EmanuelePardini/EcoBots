// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/EcoBotDataSubsystem.h"

TArray<UMaterialInterface*> UEcoBotDataSubsystem::GetEcoBotMaterials()
{
	return EcoBotMaterials;
}

void UEcoBotDataSubsystem::SetEcoBotMaterials(UMaterialInterface* Body, UMaterialInterface* Face)
{
	EcoBotMaterials[0] = Body;
	EcoBotMaterials[1] = Face;
}

FTransform UEcoBotDataSubsystem::GetEcoBotTransform()
{
	return EcoBotTransform;
}

void UEcoBotDataSubsystem::SetEcoBotTransform(FTransform NewTransform)
{
	EcoBotTransform = NewTransform;
}

TArray<float> UEcoBotDataSubsystem::GetEcoBotStats()
{
	TArray<float> Stats;
	Stats.Add(Health);
	Stats.Add(Hunger);
	Stats.Add(Thirst);

	return Stats;
}

void UEcoBotDataSubsystem::SetEcoBotStats(float NewHealth, float NewHunger, float NewThirst)
{
	Health = NewHealth;
	Hunger = NewHunger;
	Thirst = NewThirst;
}

TMap<TSubclassOf<UInventoryItem>, float> UEcoBotDataSubsystem::GetEcoBotInventory()
{
	return InventoryInfo;
}

void UEcoBotDataSubsystem::SetEcoBotInventory(TMap<TSubclassOf<UInventoryItem>, float> NewInventoryInfo)
{
	InventoryInfo = NewInventoryInfo;
}

