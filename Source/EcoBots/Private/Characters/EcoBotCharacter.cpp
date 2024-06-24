// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EcoBotCharacter.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInstance/EcoBotDataSubsystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "SaveGame/CharacterData.h"

// Sets default values
AEcoBotCharacter::AEcoBotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Camera Settings
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCamera->SetupAttachment(CameraBoom);

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	//Components
	StatsComponent = CreateDefaultSubobject<UEcoBotStatsComponent>("StatsComponent");
	StatsComponent->OnValueChanged.AddDynamic(this, &AEcoBotCharacter::OnStatsChange);
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
}

// Called when the game starts or when spawned
void AEcoBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Reference the Animation instance
	EcoBotAnim = Cast<UEcoBotAnim>(GetMesh()->GetAnimInstance());
	
	if (EcoBotWidgetClass)
	{
		// Create the widget instance
		EcoBotWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), EcoBotWidgetClass);

		if (EcoBotWidgetInstance)
		{
			// Add the widget to the viewport
			EcoBotWidgetInstance->AddToViewport();
		}
	}

	//Load the character saved data
	LoadCharacterSaved();
}

// Called every frame
void AEcoBotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(EcoBotAnim) EcoBotAnim->Animate(this);
}

void AEcoBotCharacter::Move(const FInputActionValue& Value)
{
	if(IsInteracting) return;

	// Obtains the controller's rotation and create a rotation on the yaw axis
	FVector2d MovementValue = Value.Get<FVector2d>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Gets the forward and right directions based on the Yaw rotation
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Adds movement input along the forward axis (ForwardDirection) and the right axis (RightDirection)
	AddMovementInput(ForwardDirection, MovementValue.Y);
	AddMovementInput(RightDirection, MovementValue.X);
}

void AEcoBotCharacter::DoJump()
{
	if(IsInteracting) return;
	Jump();
}

void AEcoBotCharacter::Run()
{
	if(IsInteracting) return;
	
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AEcoBotCharacter::EndRun()
{
	if(IsInteracting) return;
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AEcoBotCharacter::Interact()
{
	if(EcoBotAnim)EcoBotAnim->HasInteracted = true;
	IsInteracting = true;

	InteractionComponent->Interact(this);
}

void AEcoBotCharacter::EndInteract()
{
	if(EcoBotAnim)EcoBotAnim->HasInteracted = false;
	IsInteracting = false;
	InteractionComponent->EndInteract(this);
}


void AEcoBotCharacter::LoadCharacterSaved()
{
	if(!bIsPlayable) return;
	
	//Get Character Data
	UEcoBotDataSubsystem* EcoBotData = GetGameInstance()->GetSubsystem<UEcoBotDataSubsystem>();
	
	if(EcoBotData)
	{
		//Set Materials
		TArray<UMaterialInterface*> Materials = EcoBotData->GetEcoBotMaterials();
		if(!Materials.IsEmpty())
		{
			for (int i = 0; i <= Materials.Num()-1; i++)
			{
				if(Materials[i]) GetMesh()->SetMaterial(i, Materials[i]);
			}
		}
		
		//Set Transform
		FVector Translation = EcoBotData->GetEcoBotTransform().GetTranslation();
		if(!Translation.IsZero())
		{
			SetActorTransform(EcoBotData->GetEcoBotTransform());
		}

		//Set Stats
		if(EcoBotData->GetEcoBotStats().Num() > 0)
		{
			if(EcoBotData->GetEcoBotStats()[0] > 0)
			{
				StatsComponent->HealthStat.CurrentValue = EcoBotData->GetEcoBotStats()[0];
				StatsComponent->HealthStat.PercentValue = StatsComponent->HealthStat.CurrentValue / StatsComponent->HealthStat.MaxValue;
			}
				
			if(EcoBotData->GetEcoBotStats()[1] > 0)
			{
				StatsComponent->HungerStat.CurrentValue = EcoBotData->GetEcoBotStats()[1];
				StatsComponent->HungerStat.PercentValue = StatsComponent->HungerStat.CurrentValue / StatsComponent->HungerStat.MaxValue;
			}
				
			if(EcoBotData->GetEcoBotStats()[2] > 0)
			{
				StatsComponent->ThirstStat.CurrentValue = EcoBotData->GetEcoBotStats()[2];
				StatsComponent->ThirstStat.PercentValue = StatsComponent->ThirstStat.CurrentValue / StatsComponent->ThirstStat.MaxValue;
			}
			
			OnStatsChange(StatsComponent->HealthStat.PercentValue,
			              StatsComponent->HungerStat.PercentValue,
			               StatsComponent->ThirstStat.PercentValue);
		}

		//Set Inventory
		// if(EcoBotData->GetEcoBotInventory())
		// {
		// 	InventoryComponent->MoveAll(EcoBotData->GetEcoBotInventory());
		// }
	}
}

FCharacterData AEcoBotCharacter::GetCharacterData()
{
	FCharacterData CharacterData;

	CharacterData.BodyMat = GetMesh()->GetMaterial(0);
	CharacterData.FaceMat = GetMesh()->GetMaterial(1);
	CharacterData.ActorTransform = GetActorTransform();
	CharacterData.HealthValue = StatsComponent->HealthStat.CurrentValue;
	CharacterData.HungerValue = StatsComponent->HungerStat.CurrentValue;
	CharacterData.ThirstValue = StatsComponent->ThirstStat.CurrentValue;
	return CharacterData;
	//TODO: Interactable only by owner/server(?)
}