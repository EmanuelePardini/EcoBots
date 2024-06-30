#pragma once
#include "CoreMinimal.h"
#include "RecipeStruct.generated.h"

USTRUCT(BlueprintType)
struct FRecipeStruct
{ //TODO: 1 - Define RecipeStruct
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "ActorSaveData")
	TSubclassOf<AActor> ActorClass;
};
