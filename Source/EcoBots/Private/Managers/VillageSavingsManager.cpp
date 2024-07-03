// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/VillageSavingsManager.h"

#include "GameFramework/Character.h"
#include "GameInstance/EcoBotGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/LevelData.h"

// Sets default values
AVillageSavingsManager::AVillageSavingsManager()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVillageSavingsManager::BeginPlay()
{
	Super::BeginPlay();
	LoadLevelSaved(); // Load the saved level data when the game starts
}

// Called every frame
void AVillageSavingsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Collects and returns data about the level
FLevelData AVillageSavingsManager::GetLevelData()
{
	FLevelData LevelData;
	
	LevelData.LevelName = GetWorld()->GetCurrentLevel()->GetOuter()->GetFName(); // Get the current level name

	// Collect all actors of specified classes
	TArray<AActor*> ActorsToSave;
	for (auto ActorClassToSave : ActorClassesToSave)
	{
		TArray<AActor*> ActorsOfClass;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorClassToSave, ActorsOfClass);
		
		ActorsToSave.Append(ActorsOfClass);
	}
	
	// Save data about each actor
	for (AActor* Actor : ActorsToSave)
	{
		FActorData ActorData;
		ActorData.ActorClass = Actor->GetClass();
		ActorData.ActorTransform = Actor->GetActorTransform();
		
		LevelData.Actors.Add(ActorData);
	}
	return LevelData;
}

// Loads saved level data
void AVillageSavingsManager::LoadLevelSaved()
{
// Get the world context
    UWorld* World = GetWorld();
    
    // If the world is not valid, exit the function
    if (!World) return;

    // Get the game instance and cast it to the specific game instance class
    UEcoBotGameInstance* GameInstance = Cast<UEcoBotGameInstance>(GetGameInstance());
    if(GameInstance)
    {
        // Get the save game reference from the game instance
        UEcoBotsSaveGame* SaveGameRef = GameInstance->GetGameRef();
        
        // If the save game reference is not valid, exit the function
        if(!SaveGameRef) return;

        // Retrieve the level data from the save game reference
        FLevelData LevelData = SaveGameRef->LevelData;

        // If there are no actors saved in the level data, exit the function
        if(LevelData.Actors.IsEmpty()) return;
        
        // Iterate through each actor data in the saved level data
        for (const FActorData& ActorData : LevelData.Actors)
        {
            // Get the class of the actor to be spawned
            UClass* ActorClass = ActorData.ActorClass;
            
            // If the actor class is not valid, skip this actor
            if (!ActorClass) continue;
            
            // Spawn the actor in the world using deferred spawning
        	World->SpawnActor<AActor>(ActorClass, ActorData.ActorTransform);
        }
    }
}
