#include "Characters/EcoBotCharacter.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInstance/EcoBotDataSubsystem.h"
#include "SaveGame/CharacterData.h"

// Sets default values
AEcoBotCharacter::AEcoBotCharacter()
{
 	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera Settings
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCamera->SetupAttachment(CameraBoom);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Components
	StatsComponent = CreateDefaultSubobject<UEcoBotStatsComponent>("StatsComponent");
	StatsComponent->OnValueChanged.AddDynamic(this, &AEcoBotCharacter::OnStatsChange);
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
}

// Called when the game starts or when spawned
void AEcoBotCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Reference the Animation instance
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

	// Load the character saved data
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
	// Prevent movement if the character is interacting
	if(IsInteracting) return;

	// Obtain the controller's rotation and create a rotation on the yaw axis
	FVector2d MovementValue = Value.Get<FVector2d>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get the forward and right directions based on the Yaw rotation
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add movement input along the forward axis (ForwardDirection) and the right axis (RightDirection)
	AddMovementInput(ForwardDirection, MovementValue.Y);
	AddMovementInput(RightDirection, MovementValue.X);
}

void AEcoBotCharacter::DoJump()
{
	// Prevent jumping if the character is interacting
	if(IsInteracting) return;
	Jump();
}

void AEcoBotCharacter::Run()
{
	// Prevent running if the character is interacting
	if(IsInteracting) return;
	
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AEcoBotCharacter::EndRun()
{
	// Prevent ending run if the character is interacting
	if(IsInteracting) return;
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AEcoBotCharacter::Interact()
{
	// Set interaction state and trigger the interaction animation
	if(EcoBotAnim) EcoBotAnim->HasInteracted = true;
	IsInteracting = true;

	InteractionComponent->Interact(this);
}

void AEcoBotCharacter::EndInteract()
{
	// Reset interaction state and end the interaction animation
	if(EcoBotAnim) EcoBotAnim->HasInteracted = false;
	IsInteracting = false;
	InteractionComponent->EndInteract(this);
}

void AEcoBotCharacter::LoadCharacterSaved()
{
	// Get Character Data
	UEcoBotDataSubsystem* EcoBotData = GetGameInstance()->GetSubsystem<UEcoBotDataSubsystem>();
	
	// Check if data is valid and the character is playable
	if(!EcoBotData || !bIsPlayable) return;
	
	// Load different parts of the character data
	LoadMaterialsData(EcoBotData);
	LoadTransformData(EcoBotData);
	LoadStatsData(EcoBotData);
	LoadInventoryData(EcoBotData);
}

void AEcoBotCharacter::LoadMaterialsData(UEcoBotDataSubsystem* EcoBotData)
{
	// Load and set materials from the saved data
	TArray<UMaterialInterface*> Materials = EcoBotData->GetEcoBotMaterials();
	for (int i = 0; i < Materials.Num(); i++)
	{
		if(Materials[i]) GetMesh()->SetMaterial(i, Materials[i]);
	}
}

void AEcoBotCharacter::LoadTransformData(UEcoBotDataSubsystem* EcoBotData)
{
	// Load and set the transform from the saved data
	FVector Translation = EcoBotData->GetEcoBotTransform().GetTranslation();
	if(!Translation.IsZero()) SetActorTransform(EcoBotData->GetEcoBotTransform());
}

void AEcoBotCharacter::LoadStatsData(UEcoBotDataSubsystem* EcoBotData)
{
	// Load and set the character stats from the saved data
	const TArray<float>& Stats = EcoBotData->GetEcoBotStats();
	if (Stats.Num() > 0)
	{
		//Load the last stat value and align all parameters
		if (Stats[0] > 0) StatsComponent->UpdateStat(StatsComponent->HealthStat, Stats[0]);
		StatsComponent->UpdateStat(StatsComponent->HungerStat, Stats[1]);
		StatsComponent->UpdateStat(StatsComponent->ThirstStat, Stats[2]);

		OnStatsChange(StatsComponent->HealthStat.PercentValue, StatsComponent->HungerStat.PercentValue, StatsComponent->ThirstStat.PercentValue);
	}
}

void AEcoBotCharacter::LoadInventoryData(UEcoBotDataSubsystem* EcoBotData)
{
	// Load and set the inventory from the saved data
	TMap<TSubclassOf<UInventoryItem>, float> InventoryInfo = EcoBotData->GetEcoBotInventory();
	if(!EcoBotData->GetEcoBotInventory().IsEmpty()) InventoryComponent->LoadInventory(InventoryInfo);
}

FCharacterData AEcoBotCharacter::GetCharacterData()
{
	// Collect and return the character's current data
	FCharacterData CharacterData;

	CharacterData.BodyMat = GetMesh()->GetMaterial(0);
	CharacterData.FaceMat = GetMesh()->GetMaterial(1);
	CharacterData.ActorTransform = GetActorTransform();
	CharacterData.HealthValue = StatsComponent->HealthStat.CurrentValue;
	CharacterData.HungerValue = StatsComponent->HungerStat.CurrentValue;
	CharacterData.ThirstValue = StatsComponent->ThirstStat.CurrentValue;
	CharacterData.InventoryInfo = InventoryComponent->SaveInventory();
	return CharacterData;

	// TODO: Make interactable only by owner/server (?)
}
