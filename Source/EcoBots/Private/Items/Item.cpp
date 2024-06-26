// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Characters/EcoBotCharacter.h"
#include "Components/InventoryComponent.h"

void AItem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Rotate(DeltaSeconds);
	ManageDespawn(DeltaSeconds);
}

void AItem::Interact(AEcoBotCharacter* InteractingChar)
{
	Super::Interact(InteractingChar);
	//Add Item to the inventory on interaction
	UInventoryComponent* Inventory = InteractingChar->GetComponentByClass<UInventoryComponent>();
	Inventory->AddItem(this);
}

void AItem::Rotate(float DeltaTime)
{
	//Make the Item constantly rotate
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 90 * DeltaTime;
	SetActorRotation(NewRotation);
}

void AItem::ManageDespawn(float DeltaTime)
{
	DespawnTimer += DeltaTime;
	if(DespawnTimer >= DespawnDelay) Destroy();
}
