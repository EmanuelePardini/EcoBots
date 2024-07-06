#include "Managers/DayNightManager.h"

// Sets default values
ADayNightManager::ADayNightManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADayNightManager::BeginPlay()
{
	Super::BeginPlay();

	// Print the current time to the console and screen
	UpdateSunRotation();
}

void ADayNightManager::UpdateSunRotation()
{
	// Get the current time of the system
	FDateTime CurrentDateTime = FDateTime::Now();
	int32 Hour = CurrentDateTime.GetHour();
	int32 Minute = CurrentDateTime.GetMinute();
	int32 Second = CurrentDateTime.GetSecond();

	(Hour > 18 || (Hour >= 0 && Hour <= 6)) ? bIsNight = true : bIsNight = false;
	if(bIsNight) DirectionalSunLight->SetVisibility(false);

	// Calculate the rotation based on the time of day
	// 0 degrees is midnight, 90 degrees is 6 AM, 180 degrees is noon, 270 degrees is 6 PM
	float TotalSeconds = (Hour * 3600) + (Minute * 60) + Second;
	float RotationAngle = (TotalSeconds / 86400.0f) * 360.0f; // 86400 seconds in a day
	
	// Adjust rotation so 0 degrees is midnight, 180 degrees is noon
	// Note: Depending on your scene setup, you might need to adjust the axis
	FRotator NewRotation = FRotator( RotationAngle + AdjustmentAngle,0, 0); // Adjust pitch instead of yaw
	SetActorRotation(NewRotation);
}

// Called every frame
void ADayNightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update sun rotation based on the current time
	UpdateSunRotation();
}
