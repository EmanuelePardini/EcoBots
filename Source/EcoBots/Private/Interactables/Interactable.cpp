// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageRecharge(DeltaTime);
}

void AInteractable::ManageRecharge(float DeltaTime)
{
	if(!IsAvailable)
	{
		RechargeTimer += DeltaTime;
		if(RechargeTimer >= RechargeDelay)
		{
			IsAvailable = true;
			NotifyAvailability();
			RechargeTimer = 0;
		}
	}
}

void AInteractable::Interact(AEcoBotCharacter* InteractingChar)
{
	IInteractionInterface::Interact(InteractingChar);
	OnBeginInteract(InteractingChar);
}

void AInteractable::EndInteract(AEcoBotCharacter* InteractingChar)
{
	IInteractionInterface::EndInteract(InteractingChar);
	OnEndInteract(InteractingChar);
}

void AInteractable::SpawnItem(FVector SpawnLoc, FRotator SpawnRot)
{
	if(IsAvailable && !InteractionDatas.IsEmpty())
	{
		if(SpawnLoc.IsZero() && SpawnRot.IsZero())
		{
			SpawnLoc = GetActorLocation();
			SpawnRot = GetActorRotation();
		}
	
		for(int i=0; i <= InteractionDatas.Num()-1; i++)
		{
			
			int32 Quantity = FMath::RandRange(InteractionDatas[i].MinQuantity,InteractionDatas[i].MaxQuantity);
			if(InteractionDatas[i].ItemToSpawn)
			{
				for(int j = 0; j < Quantity; j++)
				{
					GetWorld()->SpawnActor<AInteractable>(InteractionDatas[i].ItemToSpawn,SpawnLoc,SpawnRot);
				}
			}
		}
	}
	IsAvailable = false;
}

