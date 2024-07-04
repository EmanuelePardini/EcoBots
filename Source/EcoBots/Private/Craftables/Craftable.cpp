// Fill out your copyright notice in the Description page of Project Settings.


#include "Craftables/Craftable.h"

void ACraftable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACraftable::Interact(AEcoBotCharacter* InteractingChar)
{
	Super::Interact(InteractingChar);
}
void ACraftable::EndInteract(AEcoBotCharacter* InteractingChar)
{
	Super::EndInteract(InteractingChar);
}
