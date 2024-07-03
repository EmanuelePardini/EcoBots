// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactables/Interactable.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float InteractionDistance = 1000.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* ActiveInteraction = nullptr;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Interact(AEcoBotCharacter* InteractingChar);
	void EndInteract(AEcoBotCharacter* InteractingChar);
		
};
