// Fill out your copyright notice in the Description page of Project Settings.


#include "Miscellaneous/Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>("SpawnBox");
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageSpawnTimers(DeltaTime);
}

void ASpawner::ManageSpawnTimers(float DeltaTime)
{
	// Increment the timer
	SpawnTimer += DeltaTime;

	// Check if it's time to spawn
	if (SpawnTimer >= SpawnDelay)
	{
		Spawn();
		float MinDelay = OriginSpawnDelay - SpawnDelayVariation;
		float MaxDelay = OriginSpawnDelay + SpawnDelayVariation;
		SpawnDelayVariation = FMath::RandRange(MinDelay, MaxDelay);
		SpawnTimer = 0.0f; // Reset the timer
	}
}

void ASpawner::Spawn()
{
	if(Spawneds.Num() < MaxElements)
	{
		int SpawnableIndex = FMath::RandRange(0,Spawnables.Num()-1);
	
		if (!Spawnables[SpawnableIndex]) return;
		
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBox->GetNavigationBounds());
		bool ToSpawn = FMath::RandBool();

		// Spawn the actor at the random location
		if(ToSpawn)
		{
			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Spawnables[SpawnableIndex], SpawnLocation, FRotator::ZeroRotator);
			Spawneds.Add(SpawnedActor);
		}
	}

	//Garbage collection
	for (auto Spawned : Spawneds)
	{
		if(!Spawned) Spawneds.Remove(Spawned);
	}
}

