// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveGame/LevelData.h"
#include "VillageSavingsManager.generated.h"

UCLASS()
class ECOBOTS_API AVillageSavingsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVillageSavingsManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<TSubclassOf<AActor>> ActorClassesToSave;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	FLevelData GetLevelData();
	UFUNCTION(BlueprintCallable)
	void LoadLevelSaved();
};
