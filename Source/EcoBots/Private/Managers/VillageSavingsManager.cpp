// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/VillageSavingsManager.h"
#include "GameInstance/EcoBotGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/LevelData.h"

// Sets default values
AVillageSavingsManager::AVillageSavingsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVillageSavingsManager::BeginPlay()
{
	Super::BeginPlay();
	LoadLevelSaved();
}

// Called every frame
void AVillageSavingsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FLevelData AVillageSavingsManager::GetLevelData()
{
	FLevelData LevelData;
	
	LevelData.LevelName = GetWorld()->GetCurrentLevel()->GetOuter()->GetFName();
	TArray<AActor*> ActorsToSave;
	for (auto ActorClassToSave : ActorClassesToSave)
	{
		TArray<AActor*> ActorsOfClass;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClassToSave, ActorsOfClass);
		
		ActorsToSave.Append(ActorsOfClass);
	}
	
	for (AActor* Actor : ActorsToSave)
	{
		FActorData ActorData;
		ActorData.ActorClass = Actor->GetClass();
		ActorData.ActorTransform = Actor->GetActorTransform();
		
		LevelData.Actors.Add(ActorData);
	}
	return LevelData;

}

void AVillageSavingsManager::LoadLevelSaved()
{
	UWorld* World = GetWorld();
	
	if (!World) return;

	UEcoBotGameInstance* GameInstance = Cast<UEcoBotGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		UEcoBotsSaveGame* SaveGameRef = GameInstance->GetGameRef();
		
		if(!SaveGameRef) return;

		FLevelData LevelData = SaveGameRef->LevelData;

		if(LevelData.Actors.IsEmpty()) return;
		
		for (const FActorData& ActorData : LevelData.Actors)
		{
			UClass* ActorClass = ActorData.ActorClass;
			
			if (!ActorClass) continue;
			
			AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass);
			
			if (!SpawnedActor) continue;
			
			SpawnedActor->SetActorTransform(ActorData.ActorTransform);
		}
	}
}