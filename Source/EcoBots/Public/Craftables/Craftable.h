// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Craftable.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API ACraftable : public AInteractable
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void Interact(AEcoBotCharacter* InteractingChar) override;
	virtual void EndInteract(AEcoBotCharacter* InteractingChar) override;
	virtual void ManageRecharge(float DeltaTime) override;
};
