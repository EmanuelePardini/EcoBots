// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EcoBotAnim.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/CraftComponent.h"
#include "Components/EcoBotStatsComponent.h"
#include "Components/InteractionComponent.h"
#include "Components/InventoryComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameInstance/EcoBotDataSubsystem.h"
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="States")
	bool bIsPlayable = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="States")
	bool bLookPitchFixed = true;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="States")
	bool IsInteracting = false;


	//Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UEcoBotStatsComponent* StatsComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UInteractionComponent* InteractionComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UInventoryComponent* InventoryComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UCraftComponent* CraftComponent;
	
	//Animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animations")
	UEcoBotAnim* EcoBotAnim;

	//UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> EcoBotWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UUserWidget* EcoBotWidgetInstance;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(Server, Unreliable)
	void Server_AddEcoBotWidget();
	UFUNCTION(Client, Unreliable)
	void Client_AddEcoBotWidget();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Primary Actions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void DoJump();

	//Run Manage
	UFUNCTION()
	void Run();
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_Run();
	bool Server_Run_Validate();
	void Server_Run_Implementation();

	UFUNCTION()
	void EndRun();
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_EndRun();
	bool Server_EndRun_Validate();
	void Server_EndRun_Implementation();
	
	//Interaction Manage
	UFUNCTION()
	void Interact();
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_Interact();
	bool Server_Interact_Validate();
	void Server_Interact_Implementation();
	UFUNCTION(Reliable, NetMulticast)
	void Client_Interact();
	
	UFUNCTION()
	void EndInteract();
	UFUNCTION(Reliable,Server,WithValidation)
	void Server_EndInteract();
	bool Server_EndInteract_Validate();
	void Server_EndInteract_Implementation();
	UFUNCTION(Reliable, NetMulticast)
	void Client_EndInteract();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnBeginInteract();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnEndInteract();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Die();
	
	//References
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UCameraComponent* GetCamera(){return ThirdPersonCamera;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UEcoBotAnim* GetEcoBotAnim(){return EcoBotAnim;}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UInventoryComponent* GetInventory(){return InventoryComponent;}

	//UI
	UFUNCTION(BlueprintImplementableEvent)
	void OnStatsChange(float HealthPercent, float HungerPercent, float ThirstPercent);
	UFUNCTION(BlueprintImplementableEvent)
	void OnInventoryChanged(const TArray<UInventorySlot*>& Slots);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCraftChanged(const TArray<UCraftRecipe*>& CraftRecipes);
	
	//Data Savings
	UFUNCTION(BlueprintCallable)
	void LoadCharacterSaved();
	
	void LoadMaterialsData(UEcoBotDataSubsystem* EcoBotData);
	UFUNCTION(BlueprintCallable)
	void LoadTransformData(UEcoBotDataSubsystem* EcoBotData);
	UFUNCTION(BlueprintCallable)
	void LoadStatsData(UEcoBotDataSubsystem* EcoBotData);
	UFUNCTION(BlueprintCallable)
	void LoadInventoryData(UEcoBotDataSubsystem* EcoBotData);
	UFUNCTION(BlueprintCallable)
	void LoadCraftData(UEcoBotDataSubsystem* EcoBotData);
	UFUNCTION(BlueprintCallable)
	FCharacterData GetCharacterData();
};
