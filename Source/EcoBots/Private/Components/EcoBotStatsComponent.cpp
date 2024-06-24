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
	ManageStatTimers(DeltaTime);
}



// Increment stat by a specified amount
void UEcoBotStatsComponent::IncrementStat(FStat& Stat, float Amount)
{
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
void UEcoBotStatsComponent::ManageStatTimers(float DeltaTime)
{
	// Manage hunger decrement timer
	HungerStat.DecrementTimer += DeltaTime;
	if (HungerStat.DecrementTimer >= HungerStat.DecrementDelay)
	{
		IncrementStat(HungerStat, HungerStat.DecrementAmount);
		HungerStat.DecrementTimer = 0;
	}
	
	// Manage thirst decrement timer
	ThirstStat.DecrementTimer += DeltaTime;
	if (ThirstStat.DecrementTimer >= ThirstStat.DecrementDelay)
	{
		IncrementStat(ThirstStat, ThirstStat.DecrementAmount);
		ThirstStat.DecrementTimer = 0;
	}
	
	// Manage health decrement timer if hunger or thirst is zero
	if (HungerStat.CurrentValue <= 0 || ThirstStat.CurrentValue <= 0)
	{
		HealthStat.DecrementTimer += DeltaTime;

		if (HealthStat.DecrementTimer >= HealthStat.DecrementDelay)
		{
			if (HungerStat.CurrentValue <= 0) IncrementStat(HealthStat, HealthStat.DecrementAmount);
			if (ThirstStat.CurrentValue <= 0) IncrementStat(HealthStat, HealthStat.DecrementAmount);
			HealthStat.DecrementTimer = 0;
		}
	}
}

void UEcoBotStatsComponent::UpdateStat(FStat& Stat, float Value)
{
	//Load the last stat value and align all parameters
	Stat.CurrentValue = Value;
	Stat.PercentValue = Value / Stat.MaxValue;
}

// Handle character death
void UEcoBotStatsComponent::Die()
{
	AEcoBotCharacter* EcoBotCharacter = Cast<AEcoBotCharacter>(GetOwner());
	if (EcoBotCharacter) EcoBotCharacter->Die();
}
