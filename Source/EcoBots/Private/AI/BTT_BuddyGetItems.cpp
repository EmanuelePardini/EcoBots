#include "AI/BTT_BuddyGetItems.h"
#include "AIController.h"
#include "Characters/EcoBotCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Items/Item.h"
#include "Craftables/Craftable.h"
#include "Craftables/CraftablePreview.h"

UBTT_BuddyGetItems::UBTT_BuddyGetItems()
{
    bNotifyTick = true; // Enable ticking for this task
}

EBTNodeResult::Type UBTT_BuddyGetItems::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    AEcoBotCharacter* Buddy = Cast<AEcoBotCharacter>(AIController->GetPawn());
    if (!Buddy) return EBTNodeResult::Failed;

    // Find the closest item at the beginning of the task
    TargetItem = FindClosestItem(Buddy);
    if (!TargetItem) return EBTNodeResult::Failed;

    StartTime = GetWorld()->GetTimeSeconds();
    AIController->MoveToLocation(TargetItem->GetActorLocation());
    return EBTNodeResult::InProgress;
}

void UBTT_BuddyGetItems::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

    AEcoBotCharacter* Buddy = Cast<AEcoBotCharacter>(AIController->GetPawn());
    if (!Buddy) return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    
    // Check for timeout
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - StartTime > TimeoutDuration) return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

    if (TargetItem)
    {
        // Check distance squared instead of distance for performance
        float DistanceSquared = FVector::DistSquared(Buddy->GetActorLocation(), TargetItem->GetActorLocation());
        float InteractionDistanceSquared = 250.0f * 250.0f; // Squared interaction distance

        if (DistanceSquared <= InteractionDistanceSquared)
        {
            TargetItem->Interact(Buddy);
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        }
    }
}

AItem* UBTT_BuddyGetItems::FindClosestItem(AEcoBotCharacter* Buddy)
{
    const float InteractionDistanceSquared = InteractionDistance * InteractionDistance; // Squared interaction distance

    TArray<AActor*> Items;
    UGameplayStatics::GetAllActorsOfClass(Buddy->GetWorld(), AItem::StaticClass(), Items);

    AItem* ClosestItem = nullptr;

    for (AActor* ItemActor : Items)
    {
        if (ItemActor->IsA(ACraftable::StaticClass()) || ItemActor->IsA(ACraftablePreview::StaticClass()))
            continue;

        float DistanceSquared = FVector::DistSquared(Buddy->GetActorLocation(), ItemActor->GetActorLocation());
        if (DistanceSquared < InteractionDistanceSquared)
        {
            ClosestItem = Cast<AItem>(ItemActor);
            break; // Exit early if we found an item within interaction distance
        }
    }
    
    return ClosestItem;
}
