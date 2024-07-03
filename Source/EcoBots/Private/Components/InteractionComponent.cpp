#include "Components/InteractionComponent.h"
#include "Interactables/Interactable.h"
#include "Characters/EcoBotCharacter.h"
#include "Components/InteractableComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::Interact(AEcoBotCharacter* InteractingChar)
{
	UWorld* Context = GetWorld();
	if (!Context || !InteractingChar) return;

	// Get raycast origin and direction from mouse
	FVector WorldLocation, WorldDirection;
	if (Context->GetFirstPlayerController() && Context->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector StartTrace = InteractingChar->GetCamera()->GetComponentLocation();
		FVector EndTrace = StartTrace + WorldDirection * InteractionDistance; // Adjust according to your needs

		// Perform raycast to get destination
		TArray<FHitResult> HitResults;
		FCollisionQueryParams CollisionParams;
		CollisionParams.bReturnPhysicalMaterial = false;

		if (GetWorld()->LineTraceMultiByChannel(HitResults, StartTrace, EndTrace, ECC_Visibility, CollisionParams))
		{
			// For all interaction activate the interactables
			for (const FHitResult& Hit : HitResults)
			{
				AActor* HittedActor = Hit.GetActor();
				if (!HittedActor) continue;
				
				// Check if it's an interactable actor or has an interactable component
				AInteractable* Interactable = Cast<AInteractable>(HittedActor);
				UInteractableComponent* InteractableComponent = HittedActor->FindComponentByClass<UInteractableComponent>();
				if (Interactable || InteractableComponent)
				{
					if (Interactable)
					{
						Interactable->Interact(InteractingChar);
						ActiveInteraction = Interactable;
					}
					else if (InteractableComponent)
					{
						InteractableComponent->Interact(InteractingChar);
						ActiveInteraction = InteractableComponent->GetOwner();
					}
				}
			}
		}
	}
}


void UInteractionComponent::EndInteract(AEcoBotCharacter* InteractingChar)
{
	if (ActiveInteraction)
	{
		AInteractable* Interactable = Cast<AInteractable>(ActiveInteraction);
		if (Interactable)
		{
			Interactable->EndInteract(InteractingChar);
		}
		else
		{
			UInteractableComponent* InteractableComponent = ActiveInteraction->FindComponentByClass<UInteractableComponent>();
			if (InteractableComponent)
			{
				InteractableComponent->EndInteract(InteractingChar);
			}
		}
		ActiveInteraction = nullptr;
	}
}
