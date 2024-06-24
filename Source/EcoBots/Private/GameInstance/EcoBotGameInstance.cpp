// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/EcoBotGameInstance.h"

#include "Characters/EcoBotCharacter.h"
#include "GameInstance/EcoBotDataSubsystem.h"
#include "Kismet/GameplayStatics.h"

// Loads game data from a save slot
void UEcoBotGameInstance::LoadGameData_Implementation()
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		// Cast the loaded save game to the UEcoBotsSaveGame class
		SaveGameRef = Cast<UEcoBotsSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		
		// Retrieve level and character data from the save
		FLevelData LevelData = SaveGameRef->GetLevelData();
		FCharacterData CharacterData = SaveGameRef->GetCharacterData();
		
		// Load the character data into the game
		LoadCharacterData(CharacterData);
	}
}

// Saves game data to a save slot
void UEcoBotGameInstance::SaveGameData_Implementation()
{
	UGameplayStatics::SaveGameToSlot(SaveGameRef, SlotName, 0);
}

// Loads character data into the game instance
void UEcoBotGameInstance::LoadCharacterData(FCharacterData CharacterData)
{
	// Get the EcoBot data subsystem
	UEcoBotDataSubsystem* EcoBotData = GetSubsystem<UEcoBotDataSubsystem>();
	
	// Set the character's materials, transform, stats, and inventory
	EcoBotData->SetEcoBotMaterials(CharacterData.BodyMat, CharacterData.FaceMat);
	EcoBotData->SetEcoBotTransform(CharacterData.ActorTransform);
	EcoBotData->SetEcoBotStats(CharacterData.HealthValue, CharacterData.HungerValue, CharacterData.ThirstValue);
	EcoBotData->SetEcoBotInventory(CharacterData.InventoryInfo);
}

// Creates new game data
void UEcoBotGameInstance::NewGameData_Implementation()
{
	// Create a new save game object
	SaveGameRef = Cast<UEcoBotsSaveGame>(UGameplayStatics::CreateSaveGameObject(UEcoBotsSaveGame::StaticClass()));
}

// Returns the current game data
UEcoBotsSaveGame* UEcoBotGameInstance::GetGameData_Implementation()
{
	return SaveGameRef;
}

// Saves the level and character data to the save game reference
void UEcoBotGameInstance::SaveLevelData_Implementation(FLevelData LevelData, FCharacterData CharacterData)
{
	if(!SaveGameRef) return;
	
	// Update the save game reference with the new data
	SaveGameRef->CharacterData = CharacterData;
	SaveGameRef->LevelData = LevelData;
	
	// Save the game data
	Execute_SaveGameData(this);
}

// Initializes the game instance
void UEcoBotGameInstance::Init()
{
	Super::Init();
}
