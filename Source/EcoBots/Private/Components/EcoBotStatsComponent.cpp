// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EcoBotStatsComponent.h"

#include "Characters/EcoBotCharacter.h"
#include "GameInstance/EcoBotGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEcoBotStatsComponent::UEcoBotStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize default values for stats
	HealthStat.StatName = "HealthBar";
	HealthStat.MaxValue = 1000.f;
	HealthStat.CurrentValue = 1000.f;
	HealthStat.PercentValue = HealthStat.CurrentValue / HealthStat.MaxValue;
	HealthStat.DecrementDelay = 30.f;
	HealthStat.DecrementAmount = -50.f;

	HungerStat.StatName = "HungerBar";
	HungerStat.MaxValue = 1000.f;
	HungerStat.CurrentValue = 1000.f;
	HungerStat.PercentValue = HungerStat.CurrentValue / HungerStat.MaxValue;
	HungerStat.DecrementDelay = 60.f;
	HungerStat.DecrementAmount = -50.f;

	ThirstStat.StatName = "ThirstBar";
	ThirstStat.MaxValue = 1000.f;
	ThirstStat.CurrentValue = 1000.f;
	ThirstStat.PercentValue = ThirstStat.CurrentValue / ThirstStat.MaxValue;
	ThirstStat.DecrementDelay = 40.f;
	ThirstStat.DecrementAmount = -50.f;
}


// Called when the game starts
void UEcoBotStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthStat.CurrentValue = HealthStat.MaxValue;
	HungerStat.CurrentValue = HungerStat.MaxValue;
	ThirstStat.CurrentValue = ThirstStat.MaxValue;
}


// Called every frame
void UEcoBotStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageStatTimers(DeltaTime);
}

void UEcoBotStatsComponent::IncrementHealth(float Amount)
{
	HealthStat.CurrentValue += Amount;

	if (HealthStat.CurrentValue > HealthStat.MaxValue) HealthStat.CurrentValue = HealthStat.MaxValue;
	if (HealthStat.CurrentValue <= 0)
	{
		HealthStat.CurrentValue = 0;
		Die();
	}

	HealthStat.PercentValue = HealthStat.CurrentValue / HealthStat.MaxValue;
	OnValueChanged.Broadcast(HealthStat.PercentValue, HungerStat.PercentValue, ThirstStat.PercentValue);
}

void UEcoBotStatsComponent::IncrementHunger(float Amount)
{
	HungerStat.CurrentValue += Amount;

	if (HungerStat.CurrentValue > HungerStat.MaxValue) HungerStat.CurrentValue = HungerStat.MaxValue;
	if (HungerStat.CurrentValue <= 0) HungerStat.CurrentValue = 0;

	HungerStat.PercentValue = HungerStat.CurrentValue / HungerStat.MaxValue;
	OnValueChanged.Broadcast(HealthStat.PercentValue, HungerStat.PercentValue, ThirstStat.PercentValue);
}

void UEcoBotStatsComponent::IncrementThirst(float Amount)
{
	ThirstStat.CurrentValue += Amount;

	if (ThirstStat.CurrentValue > ThirstStat.MaxValue) ThirstStat.CurrentValue = ThirstStat.MaxValue;
	if (ThirstStat.CurrentValue <= 0) ThirstStat.CurrentValue = 0;

	ThirstStat.PercentValue = ThirstStat.CurrentValue / ThirstStat.MaxValue;
	OnValueChanged.Broadcast(HealthStat.PercentValue, HungerStat.PercentValue, ThirstStat.PercentValue);
}

void UEcoBotStatsComponent::ManageStatTimers(float DeltaTime)
{
	//Hunger
	HungerStat.DecrementTimer += DeltaTime;
	if (HungerStat.DecrementTimer >= HungerStat.DecrementDelay)
	{
		IncrementHunger(HungerStat.DecrementAmount);
		HungerStat.DecrementTimer = 0;
	}
	
	//Thirst
	ThirstStat.DecrementTimer += DeltaTime;
	if (ThirstStat.DecrementTimer >= ThirstStat.DecrementDelay)
	{
		IncrementThirst(ThirstStat.DecrementAmount);
		ThirstStat.DecrementTimer = 0;
	}
	
	//Health
	if (HungerStat.CurrentValue <= 0 || ThirstStat.CurrentValue <= 0)
	{
		HealthStat.DecrementTimer += DeltaTime;

		if (HealthStat.DecrementTimer >= HealthStat.DecrementDelay)
		{
			if(HungerStat.CurrentValue<= 0) IncrementHealth(HealthStat.DecrementAmount);
			if(ThirstStat.CurrentValue<= 0) IncrementHealth(HealthStat.DecrementAmount);
			HealthStat.DecrementTimer = 0;
		}
	}
}

void UEcoBotStatsComponent::Die()
{
	AEcoBotCharacter* EcoBotCharacter = Cast<AEcoBotCharacter>(GetOwner());
	if(EcoBotCharacter) EcoBotCharacter->Die();
}

