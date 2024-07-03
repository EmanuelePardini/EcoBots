// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\AI\BTT_Patrol.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(!AIController) return EBTNodeResult::Failed;

	APawn* Pawn = AIController->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
	
	if(auto* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		
		FNavLocation NavLoc;
		FVector EnemyLoc = Pawn->GetActorLocation();
		float Radius = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(RadiusKey.SelectedKeyName);
		
		if(NavSystem->GetRandomPointInNavigableRadius(EnemyLoc,Radius,NavLoc ))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(DestinationKey.SelectedKeyName, NavLoc.Location);
		}
		
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
