// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EcoBotCharacter.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EcoBotController.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API AEcoBotController : public APlayerController
{
	GENERATED_BODY()
protected:
	//For Inputs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	class UPlayerInputData* InputData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	AEcoBotCharacter* EcoBotCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Setup")
	float InteractionDuration = 1.5f;

	
private:
	bool LookEnabled = false;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	//Primary Actions
	void Move(const FInputActionValue& Value);
	void EnableLook(const FInputActionValue& Value);
	void DisableLook(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	//Jump Manage
	void Jump(const FInputActionValue& Value);

	//Run Manage
	void Run(const FInputActionValue& Value);
	void EndRun(const FInputActionValue& Value);

	//Interaction Manage
	void Interact(const FInputActionValue& Value);
	void EndInteract();
};
