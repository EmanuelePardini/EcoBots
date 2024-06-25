// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/SaveGameInterface.h"
#include "SaveGame/EcoBotsSaveGame.h"
#include "EcoBotGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UEcoBotGameInstance : public UGameInstance,public ISaveGameInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UEcoBotsSaveGame* SaveGameRef;
	UPROPERTY(EditAnywhere)
	FString SlotName = "EcoBotOne"; //Savings defined in SelectionSlotMenu

	
	virtual void LoadGameData_Implementation() override;
	virtual void SaveGameData_Implementation() override;
	void LoadCharacterData(FCharacterData CharacterData);
	virtual void NewGameData_Implementation() override;
	virtual UEcoBotsSaveGame* GetGameData_Implementation() override;
	virtual void SaveLevelData_Implementation(FLevelData LevelData, FCharacterData CharacterData, FWorldManagerData WorldManagerData) override;
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetSlotName(){return SlotName;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UEcoBotsSaveGame* GetGameRef(){return SaveGameRef;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetSlotName(FString NewSlotName){SlotName = NewSlotName;}
	
};
