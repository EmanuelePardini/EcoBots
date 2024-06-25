// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class ECOBOTS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float OriginSpawnDelay = 3 * 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpawnDelay = 3 * 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpawnDelayVariation = 1 * 60;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SpawnTimer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<TSubclassOf<AActor>> Spawnables;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> Spawneds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UBoxComponent* SpawnBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int MaxElements = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void ManageSpawnTimers(float DeltaTime);
	UFUNCTION()
	void Spawn();
};
