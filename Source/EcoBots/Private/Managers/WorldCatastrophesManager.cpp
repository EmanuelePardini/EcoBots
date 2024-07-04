// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/WorldCatastrophesManager.h"

#include "GameInstance/EcoBotGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWorldCatastrophesManager::AWorldCatastrophesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WorldStatsComponent = CreateDefaultSubobject<UEcoBotStatsComponent>("WorldStats");
	WorldStatsComponent->OnValueChanged.AddDynamic(this, &AWorldCatastrophesManager::OnStatsChange);
	WorldStatsComponent->OnHealthFinished.AddDynamic(this, &AWorldCatastrophesManager::Die);
	WorldStatsComponent->HungerStat.bToUse = false;
	WorldStatsComponent->ThirstStat.bToUse = false;
	WorldStatsComponent->HealthStat.DecrementAmount = -10.f;
}

// Called when the game starts or when spawned
void AWorldCatastrophesManager::BeginPlay()
{
	Super::BeginPlay();
	SetWorldManagerData();
}

// Called every frame
void AWorldCatastrophesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageCatastrophes(DeltaTime);
}

void AWorldCatastrophesManager::ManageCatastrophes(float DeltaTime)
{
	CatastropheTimer += DeltaTime;

	if(CatastropheTimer >= CatastropheDelay)
	{
		CatastropheTimer = 0;
		float MinDelay = OriginCatastropheDelay - CatastropheDelayVariation;
		float MaxDelay = OriginCatastropheDelay + CatastropheDelayVariation;
		CatastropheDelay = FMath::RandRange(MinDelay, MaxDelay);
		bCatastropheProbability = FMath::RandBool();
		if(bCatastropheProbability) Catastrophe();
		
	}
}

void AWorldCatastrophesManager::Catastrophe()
{
	OnCatastrophe();
	WorldStatsComponent->IncrementStat(WorldStatsComponent->HealthStat, CatastropheDamage);

	if(ClassesToDestroy.IsEmpty()) return;
	
	TArray<AActor*> ActorsToDestroy;
	
	for(const auto ClassToDestroy : ClassesToDestroy)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToDestroy, Actors);
		ActorsToDestroy.Append(Actors);
	}

	bool bDestructionProb;
	for(const auto ActorToDestroy : ActorsToDestroy)
	{
		bDestructionProb = FMath::RandBool();
		if(bDestructionProb) ActorToDestroy->Destroy();
	}
}

FWorldManagerData AWorldCatastrophesManager::GetWorldManagerData()
{
	FWorldManagerData WorldManagerData;
	
	WorldManagerData.HealthValue = WorldStatsComponent->HealthStat.CurrentValue;
	WorldManagerData.CatastropheTimer = CatastropheTimer;

	return WorldManagerData;
}

void AWorldCatastrophesManager::SetWorldManagerData()
{
	UWorld* World = GetWorld();
	
	if (!World) return;

	UEcoBotGameInstance* GameInstance = Cast<UEcoBotGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		UEcoBotsSaveGame* SaveGameRef = GameInstance->GetGameRef();
		
		if(!SaveGameRef) return;

		FWorldManagerData WorldManagerData = SaveGameRef->WorldManagerData;
		if(WorldManagerData.HealthValue > 0)
		{
			WorldStatsComponent->UpdateStat(WorldStatsComponent->HealthStat, WorldManagerData.HealthValue);
			OnStatsChange(WorldStatsComponent->HealthStat.PercentValue);
			//Called again in blueprint if the Widget is not valid at the first try, check on BP_WorldCatastrophesManager
		}
		if(WorldManagerData.CatastropheTimer) CatastropheTimer = WorldManagerData.CatastropheTimer;
	}
}

