// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/VillageGeneratorManager.h"

// Sets default values
AVillageGeneratorManager::AVillageGeneratorManager()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVillageGeneratorManager::BeginPlay()
{
	Super::BeginPlay();
	GenerateLevel(); // Generate the level when the game starts
}

// Called every frame
void AVillageGeneratorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Generates the level by spawning pieces at anchor points
void AVillageGeneratorManager::GenerateLevel()
{
	int RandIndex; // Index for selecting a random piece from LevelPieces
	FVector SpawnLoc; // Location to spawn the new piece
	FRotator SpawnRot; // Rotation to spawn the new piece
	AActor* NewActorPiece; // The newly spawned piece
	
	// Loop through each anchor point to spawn a piece
	for(const auto AnchorPoint : AnchorPoints)
	{
		if(GeneratedPieces.Num() > 0) // If there are already generated pieces
		{
			RandIndex = FMath::RandRange(0, LevelPieces.Num() - 1); // Select a random piece
			SpawnLoc = AnchorPoint->GetActorLocation(); // Use the anchor point's location
			SpawnRot = AnchorPoint->GetActorRotation(); // Use the anchor point's rotation
			NewActorPiece = GetWorld()->SpawnActor(LevelPieces[RandIndex], &SpawnLoc, &SpawnRot);
		}
		else // If no pieces have been generated yet
		{
			SpawnLoc = GetActorLocation(); // Use the manager's location
			SpawnRot = GetActorRotation(); // Use the manager's rotation
			NewActorPiece = GetWorld()->SpawnActor(LevelPieces[0], &SpawnLoc, &SpawnRot); // Spawn the first piece
		}

		AActor* NewPiece = Cast<AActor>(NewActorPiece); // Cast the new piece to AActor
		GeneratedPieces.Add(NewPiece); // Add the new piece to the list of generated pieces
		AnchorPoint->Destroy(); // Destroy the anchor point
	}

	Destroy(); // Destroy the manager after generating the level
}
