#pragma once
#include "CoreMinimal.h"
#include "LevelData.generated.h"

USTRUCT(BlueprintType)
struct FActorData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "ActorSaveData")
	TSubclassOf<AActor> ActorClass;
	
	UPROPERTY(BlueprintReadWrite, Category = "ActorSaveData")
	FTransform ActorTransform;
};

USTRUCT(BlueprintType, Blueprintable)
struct FLevelData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FName LevelName;

	UPROPERTY(BlueprintReadWrite, Category = "LevelSaveData")
	TArray<FActorData> Actors;
	
};