// Fill out your copyright notice in the Description page of Project Settings.


#include "Craftables/Craftable.h"

void ACraftable::Tick(float DeltaSeconds)
{

}

void ACraftable::Interact(AEcoBotCharacter* InteractingChar)
{
	OnBeginInteract();
}

void ACraftable::EndInteract(AEcoBotCharacter* InteractingChar)
{
	OnEndInteract();
}
//TODO: Update Craftable