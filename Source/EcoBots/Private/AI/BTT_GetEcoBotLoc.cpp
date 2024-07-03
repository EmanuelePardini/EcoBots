#include "AI/BTT_GetEcoBotLoc.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/EcoBotCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTT_GetEcoBotLoc::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the owner actor
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}

	// Get all EcoBotCharacter actors in the world
	TArray<AActor*> EcoBotCharacters;
	UGameplayStatics::GetAllActorsOfClass(ControlledPawn->GetWorld(), AEcoBotCharacter::StaticClass(), EcoBotCharacters);

	if (EcoBotCharacters.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}

	// Find the closest EcoBotCharacter
	AActor* ClosestEcoBot = nullptr;
	float ClosestDistance = FLT_MAX;

	for (AActor* EcoBotActor : EcoBotCharacters)
	{
		if(ControlledPawn == EcoBotActor) continue;
		
		float Distance = (ControlledPawn->GetActorLocation() - EcoBotActor->GetActorLocation()).Size();
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestEcoBot = EcoBotActor;
		}
	}

	// If we found a closest EcoBotCharacter, set its location in the blackboard
	if (ClosestEcoBot)
	{
		FVector ClosestEcoBotLocation = ClosestEcoBot->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(DestinationKey.SelectedKeyName, ClosestEcoBotLocation);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
