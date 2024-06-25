#include "Components/EcoBotStatsComponent.h"
#include "Characters/EcoBotCharacter.h"

// Sets default values for this component's properties
UEcoBotStatsComponent::UEcoBotStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features off to improve performance if you don't need them.
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
}



// Called when the game starts
void UEcoBotStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize current values to max values at the start
	HealthStat.CurrentValue = HealthStat.MaxValue;
	HungerStat.CurrentValue = HungerStat.MaxValue;
	ThirstStat.CurrentValue = ThirstStat.MaxValue;
}

// Called every frame
void UEcoBotStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Manage timers for decrementing stats
	ManageStatsTimer(DeltaTime);
}



// Increment stat by a specified amount
void UEcoBotStatsComponent::IncrementStat(FStat& Stat, float Amount)
{
	if(!Stat.bToUse) return;
	
	Stat.CurrentValue += Amount;
	
	// Clamp stat value between 0 and max value
	if (Stat.CurrentValue > Stat.MaxValue) Stat.CurrentValue = Stat.MaxValue;
	if (Stat.CurrentValue <= 0)
	{
		Stat.CurrentValue = 0;
		if(Stat.StatName == HealthStat.StatName) Die();
	}
	
	// Update percentage value and broadcast change
	UpdateStat(Stat, Stat.CurrentValue);
	OnValueChanged.Broadcast(HealthStat.PercentValue, HungerStat.PercentValue, ThirstStat.PercentValue);
}

// Manage timers for decrementing stats over time
void UEcoBotStatsComponent::ManageStatsTimer(float DeltaTime)
{
	ManageSingleStatTimer(HungerStat, DeltaTime);
	ManageSingleStatTimer(ThirstStat, DeltaTime);
	
	// Manage health decrement timer if hunger or thirst is zero or is not to use
	if ((HungerStat.CurrentValue <= 0 || !HungerStat.bToUse) || (ThirstStat.CurrentValue <= 0 || !ThirstStat.bToUse))
		ManageSingleStatTimer(HealthStat, DeltaTime);
}

void UEcoBotStatsComponent::ManageSingleStatTimer(FStat& Stat, float DeltaTime)
{
	if(!Stat.bToUse) return;
	
	Stat.DecrementTimer += DeltaTime;
	if (Stat.DecrementTimer >= Stat.DecrementDelay)
	{
		IncrementStat(Stat, Stat.DecrementAmount);
		Stat.DecrementTimer = 0;
	}
}

void UEcoBotStatsComponent::UpdateStat(FStat& Stat, float Value)
{
	if(!Stat.bToUse) return;
	
	//Load the last stat value and align all parameters
	Stat.CurrentValue = Value;
	Stat.PercentValue = Value / Stat.MaxValue;
}

// Handle character death
void UEcoBotStatsComponent::Die()
{
	OnHealthFinished.Broadcast();
}
