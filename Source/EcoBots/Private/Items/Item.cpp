// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Characters/EcoBotCharacter.h"
#include "Components/InventoryComponent.h"

void AItem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 90 * DeltaSeconds;
	SetActorRotation(NewRotation);
}

void AItem::Interact(AEcoBotCharacter* InteractingChar)
{
	Super::Interact(InteractingChar);

	UInventoryComponent* Inventory = InteractingChar->GetComponentByClass<UInventoryComponent>();
	Inventory->AddItem(this);
}
