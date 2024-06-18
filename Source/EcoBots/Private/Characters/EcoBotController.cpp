// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EcoBotController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/PlayerInputData.h"

void AEcoBotController::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC, 0);
	}

	//Reference to the Character possessed
	EcoBotCharacter = Cast<AEcoBotCharacter>(GetPawn());

	// Set the input mode to Game and UI
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	// Show the mouse cursor
	bShowMouseCursor = true;
}

void AEcoBotController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEcoBotController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Moving
		EnhancedInputComponent->BindAction(InputData->Move, ETriggerEvent::Triggered, this, &AEcoBotController::Move);
		
		//Jumping
		EnhancedInputComponent->BindAction(InputData->Jump, ETriggerEvent::Triggered, this, &AEcoBotController::Jump);

		//Running
		EnhancedInputComponent->BindAction(InputData->Run, ETriggerEvent::Started, this, &AEcoBotController::Run);
		EnhancedInputComponent->BindAction(InputData->Run, ETriggerEvent::Completed, this, &AEcoBotController::EndRun);
		
		//Interacting
		EnhancedInputComponent->BindAction(InputData->Interact, ETriggerEvent::Started, this, &AEcoBotController::Interact);
	}
}

void AEcoBotController::Move(const FInputActionValue& Value)
{
	if(EcoBotCharacter) EcoBotCharacter->Move(Value);
}

void AEcoBotController::Jump(const FInputActionValue& Value)
{
	if(EcoBotCharacter) EcoBotCharacter->DoJump();
}

void AEcoBotController::Run(const FInputActionValue& Value)
{
	if(EcoBotCharacter) EcoBotCharacter->Run();
}

void AEcoBotController::EndRun(const FInputActionValue& Value)
{
	if(EcoBotCharacter) EcoBotCharacter->EndRun();
}

void AEcoBotController::Interact(const FInputActionValue& Value)
{
	if(EcoBotCharacter) EcoBotCharacter->Interact();
	
	FTimerHandle InteractTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(InteractTimerHandle, this, &AEcoBotController::EndInteract, InteractionDuration, false);
}

void AEcoBotController::EndInteract()
{
	if(EcoBotCharacter) EcoBotCharacter->EndInteract();
}
