// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
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

// Manages the recharge timer and availability of the interactable object
void AInteractable::ManageRecharge(float DeltaTime)
{
	if(!IsAvailable)
	{
		RechargeTimer += DeltaTime;
		if(RechargeTimer >= RechargeDelay)
		{
			// Make the object available again and reset the timer
			IsAvailable = true;
			NotifyAvailability();
			RechargeTimer = 0;
		}
	}
}

// Handles interaction with the interactable object
void AInteractable::Interact(AEcoBotCharacter* InteractingChar)
{
	IInteractionInterface::Interact(InteractingChar);
	OnBeginInteract(InteractingChar);
}

// Handles end of interaction with the interactable object
void AInteractable::EndInteract(AEcoBotCharacter* InteractingChar)
{
	IInteractionInterface::EndInteract(InteractingChar);
	OnEndInteract(InteractingChar);
	// Set the object to not available after spawning items
	IsAvailable = false;
}

// Spawns items at the specified location and rotation
void AInteractable::SpawnItem(FVector SpawnLoc, FRotator SpawnRot)
{
	if(IsAvailable && !InteractionDatas.IsEmpty())
	{
		// If the spawn location and rotation are zero, use the actor's location and rotation
		if(SpawnLoc.IsZero() && SpawnRot.IsZero())
		{
			SpawnLoc = GetActorLocation();
			SpawnRot = GetActorRotation();
		}
	
		// Loop through each interaction data to spawn items
		for(int i = 0; i <= InteractionDatas.Num() - 1; i++)
		{
			int32 Quantity = FMath::RandRange(InteractionDatas[i].MinQuantity, InteractionDatas[i].MaxQuantity);
			
			if(InteractionDatas[i].ItemToSpawn)
			{
				// Spawn the specified quantity of items
				for(int j = 0; j < Quantity; j++)
				{
					FVector RandomOffset = FVector(
						FMath::RandRange(-InteractionDatas[i].ItemSpawnRadius, InteractionDatas[i].ItemSpawnRadius),
						FMath::RandRange(-InteractionDatas[i].ItemSpawnRadius, InteractionDatas[i].ItemSpawnRadius),
						InteractionDatas[i].ItemSpawnRadius);
					
					FVector RandomSpawnLoc = SpawnLoc + RandomOffset;
					
					if(!InteractionDatas[i].bToInheritRotation)
					{
						SpawnRot = FRotator(0, 0, 0);
					}
					
					GetWorld()->SpawnActor<AInteractable>(InteractionDatas[i].ItemToSpawn, RandomSpawnLoc, SpawnRot);
				}
			}
		}
	}
}
