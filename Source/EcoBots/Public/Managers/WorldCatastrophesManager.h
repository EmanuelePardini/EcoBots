// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EcoBotStatsComponent.h"
#include "GameFramework/Actor.h"
#include "WorldCatastrophesManager.generated.h"

UCLASS()
class ECOBOTS_API AWorldCatastrophesManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldCatastrophesManager();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float BaseDuration = 360;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float DurationRange = 180;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	bool bIsActive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UEcoBotStatsComponent* WorldStatsComponent;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ManageCatastrophes(float DeltaTime);
};
