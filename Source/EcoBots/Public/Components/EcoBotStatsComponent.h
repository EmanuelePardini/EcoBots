 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Stat.h"
#include "Components/ActorComponent.h"
#include "EcoBotStatsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UEcoBotStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEcoBotStatsComponent();
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStat HealthStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStat HungerStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStat ThirstStat;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnValueChanged,float, HealthPercent, float, HungerPercent, float, ThirstPercent);
	FOnValueChanged OnValueChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void IncrementStat(FStat& Stat, float Amount);
	UFUNCTION()
	void ManageStatTimers(float DeltaTime);
	UFUNCTION()
	void UpdateStat(FStat& Stat, float Value);
	UFUNCTION()
	void Die();
};
