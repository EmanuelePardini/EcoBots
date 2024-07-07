// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VillageGeneratorManager.generated.h"

USTRUCT(BlueprintType)
struct FBiome
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<TSubclassOf<AActor>> LevelPieces;
};

UCLASS()
class ECOBOTS_API AVillageGeneratorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageGeneratorManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	TArray<AActor*> AnchorPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> GeneratedPieces;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<FBiome> Biomes; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(Server, Reliable)
	void GenerateLevel();
};
