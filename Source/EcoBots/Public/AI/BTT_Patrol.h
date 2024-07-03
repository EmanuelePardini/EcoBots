// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UBTT_Patrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category ="Setup")
	FBlackboardKeySelector RadiusKey;
	UPROPERTY(EditAnywhere, Category ="Setup")
	FBlackboardKeySelector DestinationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
