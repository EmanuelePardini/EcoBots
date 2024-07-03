#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Items/Item.h"
#include "BTT_BuddyGetItems.generated.h"

UCLASS()
class ECOBOTS_API UBTT_BuddyGetItems : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_BuddyGetItems();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AItem* FindClosestItem(AEcoBotCharacter* Buddy);
    
	float StartTime;
	float InteractionDistance = 5000;
	float TimeoutDuration = 45.0f;// Set the desired timeout duration
	UPROPERTY()
	AItem* TargetItem;
};
