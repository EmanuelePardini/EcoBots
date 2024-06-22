 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EcoBotStatsComponent.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FName StatName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PercentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float DecrementDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float DecrementTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decrement")
	float DecrementAmount;
	
	

	FStat()
		: StatName("Stat")
		, MaxValue(1000.f)
		, CurrentValue(1000.f)
		, PercentValue(1.f)
		, DecrementDelay(60.f)
		, DecrementTimer(0.f)
		, DecrementAmount(-50.f)
	{
	}
};

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
	void IncrementHealth(float Amount);
	UFUNCTION()
	void IncrementHunger(float Amount);
	UFUNCTION()
	void IncrementThirst(float Amount);

	UFUNCTION()
	void ManageStatTimers(float DeltaTime);

	UFUNCTION()
	void Die();
};
