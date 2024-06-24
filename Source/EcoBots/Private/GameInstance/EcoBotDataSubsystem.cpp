// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EcoBotDataSubsystem.h"

// Returns the EcoBot's materials
TArray<UMaterialInterface*> UEcoBotDataSubsystem::GetEcoBotMaterials()
{
	return EcoBotMaterials;
}

// Sets the EcoBot's body and face materials
void UEcoBotDataSubsystem::SetEcoBotMaterials(UMaterialInterface* Body, UMaterialInterface* Face)
{
	EcoBotMaterials[0] = Body;
	EcoBotMaterials[1] = Face;
}

// Returns the EcoBot's transform
FTransform UEcoBotDataSubsystem::GetEcoBotTransform()
{
	return EcoBotTransform;
}

// Sets the EcoBot's transform
void UEcoBotDataSubsystem::SetEcoBotTransform(FTransform NewTransform)
{
	EcoBotTransform = NewTransform;
}

// Returns the EcoBot's stats as an array of floats
TArray<float> UEcoBotDataSubsystem::GetEcoBotStats()
{
	TArray<float> Stats;
	Stats.Add(Health);
	Stats.Add(Hunger);
	Stats.Add(Thirst);

	return Stats;
}

// Sets the EcoBot's stats
void UEcoBotDataSubsystem::SetEcoBotStats(float NewHealth, float NewHunger, float NewThirst)
{
	Health = NewHealth;
	Hunger = NewHunger;
	Thirst = NewThirst;
}

// Returns the EcoBot's inventory as a map
TMap<TSubclassOf<UInventoryItem>, float> UEcoBotDataSubsystem::GetEcoBotInventory()
{
	return InventoryInfo;
}

// Sets the EcoBot's inventory
void UEcoBotDataSubsystem::SetEcoBotInventory(TMap<TSubclassOf<UInventoryItem>, float> NewInventoryInfo)
{
	InventoryInfo = NewInventoryInfo;
}
