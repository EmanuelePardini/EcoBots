// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelData.h"
#include "CharacterData.h"
#include "WorldManagerData.h"
#include "GameFramework/SaveGame.h"
#include "EcoBotsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UEcoBotsSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FLevelData LevelData;
	UPROPERTY(EditAnywhere)
	FCharacterData CharacterData;
	UPROPERTY(EditAnywhere)
	FWorldManagerData WorldManagerData;
	
	UFUNCTION()
	FORCEINLINE FLevelData GetLevelData(){return LevelData;}
	UFUNCTION()
	FORCEINLINE FCharacterData GetCharacterData(){return CharacterData;}
	UFUNCTION()
	FORCEINLINE FWorldManagerData GetWorldManagerData(){return WorldManagerData;}
};
