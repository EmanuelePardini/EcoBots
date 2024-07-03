// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EcoBotAIController.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API AEcoBotAIController : public AAIController
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category ="Setup")
	FString RadiusKey;
	UPROPERTY(EditAnywhere, Category="Setup")
	float PatrolRadius = 100.f;
	UPROPERTY(EditAnywhere, Category="Setup")
	UBehaviorTree* Behavior;
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
