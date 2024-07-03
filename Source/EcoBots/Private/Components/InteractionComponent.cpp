// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"
#include "Interactables/Interactable.h"
#include "Characters/EcoBotCharacter.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::Interact(AEcoBotCharacter* InteractingChar)
{
	UWorld* Context = GetWorld();
	FVector StartTrace;
	FVector EndTrace;

	// Get raycast origin and direction from mouse
	FVector WorldLocation, WorldDirection;
	if (Context->GetFirstPlayerController())
	{
		Context->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	}

	// Calculate end of raycast
	StartTrace = InteractingChar->GetCamera()->GetComponentLocation();
	EndTrace = StartTrace + WorldDirection * InteractionDistance; // Arbitrary length, you can adjust it according to your needs

	// Perform raycast to get destination
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceMultiByChannel(HitResults, StartTrace, EndTrace, ECC_MAX, CollisionParams))
	{
		//For all interaction activate the interactables
		for(FHitResult Hit : HitResults)
		{
			AActor* HittedActor = Hit.GetActor();
			AInteractable* Interactable = Cast<AInteractable>(HittedActor);
			if(Interactable)
			{
				float Distance = FVector::Dist(InteractingChar->GetActorLocation(), HittedActor->GetActorLocation());
				if(Distance <= InteractionDistance) Interactable->Interact(InteractingChar);
				ActiveInteraction = Interactable;
			}
		}
	}
}


void UInteractionComponent::EndInteract(AEcoBotCharacter* InteractingChar)
{
	if(ActiveInteraction) ActiveInteraction->EndInteract(InteractingChar);
	ActiveInteraction = nullptr;
}

