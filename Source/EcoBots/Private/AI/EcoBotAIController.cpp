// Fill out your copyright notice in the Description page of Project Settings.


#include "AI\EcoBotAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEcoBotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
	UBlackboardComponent* BlackboardComponent;
	if(Behavior)
	{
		UseBlackboard(Behavior->BlackboardAsset, BlackboardComponent);
		Blackboard = BlackboardComponent;
		Blackboard->SetValueAsFloat(*RadiusKey, PatrolRadius);
	
		RunBehaviorTree(Behavior);
	}
}
