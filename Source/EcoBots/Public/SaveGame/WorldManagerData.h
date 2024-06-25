#pragma once
#include "CoreMinimal.h"
#include "WorldManagerData.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FWorldManagerData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthValue;
	
};