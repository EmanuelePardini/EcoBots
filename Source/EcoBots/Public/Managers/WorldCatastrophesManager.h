// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/EcoBotStatsComponent.h"
#include "GameFramework/Actor.h"
#include "SaveGame/WorldManagerData.h"
#include "WorldCatastrophesManager.generated.h"

UCLASS()
class ECOBOTS_API AWorldCatastrophesManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldCatastrophesManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	UEcoBotStatsComponent* WorldStatsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	bool bCatastropheProbability = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float OriginCatastropheDelay = 15 * 60; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float CatastropheDelay = 15 * 60; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float CatastropheDelayVariation = 5 * 60; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<TSubclassOf<AActor>> ClassesToDestroy;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CatastropheTimer = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float CatastropheDamage = -400.f;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ManageCatastrophes(float DeltaTime);
	void Catastrophe();
	UFUNCTION(BlueprintImplementableEvent)
	void OnCatastrophe();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnStatsChange(float HealthPercent, float HungerPercent = 0, float ThirstPercent = 0 );
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	FWorldManagerData GetWorldManagerData();
	UFUNCTION(BlueprintCallable)
	void SetWorldManagerData();
};
