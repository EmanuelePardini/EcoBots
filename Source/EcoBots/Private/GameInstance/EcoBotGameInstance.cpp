// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/EcoBotGameInstance.h"

#include "Characters/EcoBotCharacter.h"
#include "GameInstance\EcoBotDataSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UEcoBotGameInstance::LoadGameData_Implementation()
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveGameRef = Cast<UEcoBotsSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		FLevelData LevelData = SaveGameRef->GetLevelData();
		FCharacterData CharacterData = SaveGameRef->GetCharacterData();
		UEcoBotDataSubsystem* EcoBotData = GetSubsystem<UEcoBotDataSubsystem>();
		EcoBotData->SetEcoBotMaterials(CharacterData.BodyMat, CharacterData.FaceMat);
		EcoBotData->SetEcoBotTransform(CharacterData.ActorTransform);
		
		UGameplayStatics::OpenLevel(GetWorld(), ContinueLevel);
	}
	else
	{
		Execute_NewGameData(this);
	}
}

void UEcoBotGameInstance::SaveGameData_Implementation()
{
	UGameplayStatics::SaveGameToSlot(SaveGameRef, SlotName, 0);
}

void UEcoBotGameInstance::NewGameData_Implementation()
{
	SaveGameRef = Cast<UEcoBotsSaveGame>(UGameplayStatics::CreateSaveGameObject(UEcoBotsSaveGame::StaticClass()));
	UGameplayStatics::OpenLevel(GetWorld(), NewGameLevel);
}


UEcoBotsSaveGame* UEcoBotGameInstance::GetGameData_Implementation()
{
	return SaveGameRef;
}

void UEcoBotGameInstance::SaveLevelData_Implementation(FLevelData LevelData, FCharacterData CharacterData)
{
	SaveGameRef->CharacterData = CharacterData;
	SaveGameRef->LevelData = LevelData;
	
	Execute_SaveGameData(this);
}

void UEcoBotGameInstance::Init()
{
	Super::Init();
}