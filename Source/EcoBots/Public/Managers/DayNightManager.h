// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DirectionalLightComponent.h"
#include "GameFramework/Actor.h"
#include "DayNightManager.generated.h"

UCLASS()
class ECOBOTS_API ADayNightManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightManager();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UDirectionalLightComponent* DirectionalSunLight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float AdjustmentAngle = 90.f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void UpdateSunRotation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
