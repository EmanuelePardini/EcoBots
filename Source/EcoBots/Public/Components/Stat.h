#pragma once
#include "CoreMinimal.h"
#include "Stat.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FName StatName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PercentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float DecrementDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float DecrementTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decrement")
	float DecrementAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decrement")
	bool bToUse;
	
	

	FStat()
		: StatName("Stat")
		, MaxValue(1000.f)
		, CurrentValue(1000.f)
		, PercentValue(1.f)
		, DecrementDelay(60.f)
		, DecrementTimer(0.f)
		, DecrementAmount(-50.f)
		, bToUse(true)
	{
	}
};