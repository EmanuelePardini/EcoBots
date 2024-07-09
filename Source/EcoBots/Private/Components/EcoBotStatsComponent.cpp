#include "Components/EcoBotStatsComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UEcoBotStatsComponent::UEcoBotStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize default values for stats
	HealthStat.StatName = "HealthBar";
	HealthStat.MaxValue = 1000.f;
	HealthStat.CurrentValue = 1000.f;
	HealthStat.PercentValue = HealthStat.CurrentValue / HealthStat.MaxValue;
	HealthStat.DecrementDelay = 30.f;
	HealthStat.DecrementAmount = -50.f;
	HealthStat.bToUse = true;

	HungerStat.StatName = "HungerBar";
	HungerStat.MaxValue = 1000.f;
	HungerStat.CurrentValue = 1000.f;
	HungerStat.PercentValue = HungerStat.CurrentValue / HungerStat.MaxValue;
	HungerStat.DecrementDelay = 60.f;
	HungerStat.DecrementAmount = -50.f;
	HungerStat.bToUse = true;

	ThirstStat.StatName = "ThirstBar";
	ThirstStat.MaxValue = 1000.f;
	ThirstStat.CurrentValue = 1000.f;
	ThirstStat.PercentValue = ThirstStat.CurrentValue / ThirstStat.MaxValue;
	ThirstStat.DecrementDelay = 40.f;
	ThirstStat.DecrementAmount = -50.f;
	ThirstStat.bToUse = true;

	SetIsReplicatedByDefault(true);
}

void UEcoBotStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthStat.CurrentValue = HealthStat.MaxValue;
	HungerStat.CurrentValue = HungerStat.MaxValue;
	ThirstStat.CurrentValue = ThirstStat.MaxValue;
}

void UEcoBotStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ManageStatsTimer(DeltaTime);
}

void UEcoBotStatsComponent::IncrementHealth(float Amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		UpdateHealth(HealthStat.CurrentValue + Amount);
	}
	else
	{
		Server_IncrementHealth(Amount);
	}
}

void UEcoBotStatsComponent::IncrementHunger(float Amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		UpdateHunger(HungerStat.CurrentValue + Amount);
	}
	else
	{
		Server_IncrementHunger(Amount);
	}
}

void UEcoBotStatsComponent::IncrementThirst(float Amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		UpdateThirst(ThirstStat.CurrentValue + Amount);
	}
	else
	{
		Server_IncrementThirst(Amount);
	}
}

bool UEcoBotStatsComponent::Server_IncrementHealth_Validate(float Amount)
{
	return true;
}

void UEcoBotStatsComponent::Server_IncrementHealth_Implementation(float Amount)
{
	IncrementHealth(Amount);
}

bool UEcoBotStatsComponent::Server_IncrementHunger_Validate(float Amount)
{
	return true;
}

void UEcoBotStatsComponent::Server_IncrementHunger_Implementation(float Amount)
{
	IncrementHunger(Amount);
}

bool UEcoBotStatsComponent::Server_IncrementThirst_Validate(float Amount)
{
	return true;
}

void UEcoBotStatsComponent::Server_IncrementThirst_Implementation(float Amount)
{
	IncrementThirst(Amount);
}

void UEcoBotStatsComponent::ManageStatsTimer(float DeltaTime)
{
	ManageHealthTimer(DeltaTime);
	ManageHungerTimer(DeltaTime);
	ManageThirstTimer(DeltaTime);
}

void UEcoBotStatsComponent::ManageHealthTimer(float DeltaTime)
{
	if (!HealthStat.bToUse) return;

	HealthStat.DecrementTimer += DeltaTime;
	if (HealthStat.DecrementTimer >= HealthStat.DecrementDelay)
	{
		IncrementHealth(HealthStat.DecrementAmount);
		HealthStat.DecrementTimer = 0;
	}
}

void UEcoBotStatsComponent::ManageHungerTimer(float DeltaTime)
{
	if (!HungerStat.bToUse) return;

	HungerStat.DecrementTimer += DeltaTime;
	if (HungerStat.DecrementTimer >= HungerStat.DecrementDelay)
	{
		IncrementHunger(HungerStat.DecrementAmount);
		HungerStat.DecrementTimer = 0;
	}
}

void UEcoBotStatsComponent::ManageThirstTimer(float DeltaTime)
{
	if (!ThirstStat.bToUse) return;

	ThirstStat.DecrementTimer += DeltaTime;
	if (ThirstStat.DecrementTimer >= ThirstStat.DecrementDelay)
	{
		IncrementThirst(ThirstStat.DecrementAmount);
		ThirstStat.DecrementTimer = 0;
	}
}

void UEcoBotStatsComponent::UpdateHealth(float Value)
{
	if (!HealthStat.bToUse) return;

	HealthStat.CurrentValue = FMath::Clamp(Value, 0.0f, HealthStat.MaxValue);
	HealthStat.PercentValue = HealthStat.CurrentValue / HealthStat.MaxValue;

	OnValueChanged.Broadcast(HealthStat.PercentValue, HungerStat.PercentValue, ThirstStat.PercentValue);

	if (HealthStat.CurrentValue <= 0)
	{
		Die();
	}
}

void UEcoBotStatsComponent::UpdateHunger(float Value)
{
	if (!HungerStat.bToUse) return;

	HungerStat.CurrentValue = FMath::Clamp(Value, 0.0f, HungerStat.MaxValue);
	HungerStat.PercentValue = HungerStat.CurrentValue / HungerStat.MaxValue;

	OnValueChanged.Broadcast(HealthStat.PercentValue, HungerStat.PercentValue, ThirstStat.PercentValue);
}

void UEcoBotStatsComponent::UpdateThirst(float Value)
{
	if (!ThirstStat.bToUse) return;

	ThirstStat.CurrentValue = FMath::Clamp(Value, 0.0f, ThirstStat.MaxValue);
	ThirstStat.PercentValue = ThirstStat.CurrentValue / ThirstStat.MaxValue;

	OnValueChanged.Broadcast(HealthStat.PercentValue, HungerStat.PercentValue, ThirstStat.PercentValue);
}

void UEcoBotStatsComponent::Die()
{
	OnHealthFinished.Broadcast();
}

