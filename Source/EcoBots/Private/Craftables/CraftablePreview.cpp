// Fill out your copyright notice in the Description page of Project Settings.


#include "Craftables/CraftablePreview.h"
#include "Characters/EcoBotCharacter.h"

void ACraftablePreview::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(EcoBotReference) ManagePreview();
}

void ACraftablePreview::ManagePreview()
{
	SetActorLocation(EcoBotReference->GetActorLocation());
	SetActorRotation(EcoBotReference->GetActorRotation());
}

void ACraftablePreview::SetCraftRecipe(TArray<FCraftMaterialCost> MaterialCosts)
{
	NeededMaterials = MaterialCosts;
}

void ACraftablePreview::SetEcoBotReference(AEcoBotCharacter* NewEcoBot)
{
	EcoBotReference = NewEcoBot;
}

void ACraftablePreview::Interact(AEcoBotCharacter* InteractingChar)
{
	Super::Interact(InteractingChar);
	SpawnCraft();
}

void ACraftablePreview::SpawnCraft()
{
	// Remove materials from inventory
	for (const FCraftMaterialCost& MaterialCost : NeededMaterials)
	{
		for (int32 i = 0; i < MaterialCost.Quantity; ++i)
		{
			EcoBotReference->GetInventory()->UseItemByClass(MaterialCost.RequiredMaterial, MaterialCost.Quantity);
		}
	}

	// Spawn the crafted item
	GetWorld()->SpawnActor<ACraftable>(CraftableToSpawn, GetActorLocation(), GetActorRotation());
	Destroy();
}
