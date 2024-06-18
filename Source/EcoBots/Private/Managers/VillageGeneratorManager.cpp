// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/VillageGeneratorManager.h"

// Sets default values
AVillageGeneratorManager::AVillageGeneratorManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVillageGeneratorManager::BeginPlay()
{
	Super::BeginPlay();
	GenerateLevel();
}

// Called every frame
void AVillageGeneratorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVillageGeneratorManager::GenerateLevel()
{
	int RandIndex;
	FVector SpawnLoc;
	FRotator SpawnRot;
	AActor* NewActorPiece;
	
	for(const auto AnchorPoint : AnchorPoints)
	{

		if(GeneratedPieces.Num() > 0)
		{
			RandIndex = FMath::RandRange(0, LevelPieces.Num()-1);
			SpawnLoc = AnchorPoint->GetActorLocation();
			SpawnRot = AnchorPoint->GetActorRotation();
			NewActorPiece = GetWorld()->SpawnActor(LevelPieces[RandIndex], &SpawnLoc, &SpawnRot);
		}
		else
		{
			SpawnLoc = GetActorLocation();
			SpawnRot = GetActorRotation();
			NewActorPiece = GetWorld()->SpawnActor(LevelPieces[0], &SpawnLoc, &SpawnRot);
		}
		AActor* NewPiece = Cast<AActor>(NewActorPiece);
		GeneratedPieces.Add(NewPiece);
		AnchorPoint->Destroy();
	}
	Destroy();
}

