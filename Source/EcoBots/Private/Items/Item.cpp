// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Characters/EcoBotCharacter.h"
#include "Components/InventoryComponent.h"

void AItem::Interact(AEcoBotCharacter* InteractingChar)
{
	Super::Interact(InteractingChar);

	UInventoryComponent* Inventory = InteractingChar->GetComponentByClass<UInventoryComponent>();
	Inventory->AddItem(this);
}
