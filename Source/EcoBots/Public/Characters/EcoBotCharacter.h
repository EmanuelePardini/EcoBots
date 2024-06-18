// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EcoBotAnim.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/EcoBotStatsComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SaveGame/CharacterData.h"
#include "EcoBotCharacter.generated.h"

UCLASS()
class ECOBOTS_API AEcoBotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEcoBotCharacter();

protected:
	//Camera Declaration
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Camera")
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Camera")
	UCameraComponent* ThirdPersonCamera;
	
	//Movement
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Movement")
	float WalkSpeed = 250.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Movement")
	float RunSpeed = 500.f;

	//Input States
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="States")
	bool IsInteracting = false;

	//Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UEcoBotStatsComponent* StatsComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UInteractionComponent* InteractionComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UInventoryComponent* InventoryComponent;
	//Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animations")
	UEcoBotAnim* EcoBotAnim;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Primary Actions
	void Move(const FInputActionValue& Value);
	void DoJump();

	//Run Manage
	void Run();
	void EndRun();

	//Interaction Manage
	void Interact();
	void EndInteract();
	
	//Game Save
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCameraComponent* GetCamera(){return ThirdPersonCamera;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UEcoBotAnim* GetEcoBotAnim(){return EcoBotAnim;}
	UFUNCTION(BlueprintCallable)
	void LoadCharacterSaved();
	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData();
};
