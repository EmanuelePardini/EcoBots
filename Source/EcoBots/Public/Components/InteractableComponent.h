// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractableComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UInteractableComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	virtual void Interact(AEcoBotCharacter* InteractingChar  = nullptr) override;
	UFUNCTION(BlueprintCallable)
	virtual void EndInteract(AEcoBotCharacter* InteractingChar  = nullptr) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnBeginInteract(AEcoBotCharacter* InteractingChar = nullptr);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnEndInteract(AEcoBotCharacter* InteractingChar  = nullptr);
		
};
