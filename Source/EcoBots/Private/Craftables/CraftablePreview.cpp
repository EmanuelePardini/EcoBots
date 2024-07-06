// Fill out your copyright notice in the Description page of Project Settings.


#include "Craftables/CraftablePreview.h"
#include "Characters/EcoBotCharacter.h"
#include "Components/WidgetInteractionComponent.h"
#include "Kismet/GameplayStatics.h"

ACraftablePreview::ACraftablePreview()
{
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>("PreviewMesh");
	RootComponent = PreviewMesh;
	DiscardWidget = CreateDefaultSubobject<UWidgetComponent>("DiscardWidget");
	DiscardWidget->SetupAttachment(RootComponent);
	CraftWidget = CreateDefaultSubobject<UWidgetComponent>("CraftWidget");
	CraftWidget->SetupAttachment(RootComponent);
}

void ACraftablePreview::BeginPlay()
{
	Super::BeginPlay();
}

void ACraftablePreview::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (DiscardWidget) UpdateWidgetRotation(DiscardWidget);
	if (CraftWidget) UpdateWidgetRotation(CraftWidget);
	if(IsPlacing && EcoBotReference) ManagePreviewPlacing();
}


void ACraftablePreview::UpdateWidgetRotation(UWidgetComponent* ActionsWidget)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		FVector WidgetLocation = ActionsWidget->GetComponentLocation();
		FVector PlayerLocation;
		FRotator PlayerRotation;
		PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

		FRotator LookAtRotation = FRotationMatrix::MakeFromX(PlayerLocation - WidgetLocation).Rotator();
		ActionsWidget->SetWorldRotation(LookAtRotation);
	}
}

void ACraftablePreview::ManagePreviewPlacing()
{
	FVector ForwardVector = EcoBotReference->GetActorForwardVector();
	FVector StartLocation = EcoBotReference->GetActorLocation() + ForwardVector * 250.f;
	FVector EndLocation = StartLocation - FVector(0, 0, 1000.0f); // Trace down 1000 units

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(EcoBotReference);
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		FVector PreviewLocation = FVector(StartLocation.X, StartLocation.Y, HitResult.Location.Z); // Impact Point with ground

		// Calculate Actor Bounding Box to start from bottom
		if(ToApplyZOffset) //To use in case scale or blueprint location is not original
			{
			FVector Origin;
			FVector BoxExtent;
			GetActorBounds(false, Origin, BoxExtent);

			// Apply OffSet to Location
			PreviewLocation.Z += BoxExtent.Z;
			}
		
		SetActorLocation(PreviewLocation);
		SetActorRotation(EcoBotReference->GetActorRotation());
	}
}

void ACraftablePreview::SetCraftRecipe(TArray<FCraftMaterialCost> MaterialCosts)
{
	NeededMaterials = MaterialCosts;
}

void ACraftablePreview::SetEcoBotReference(AEcoBotCharacter* NewEcoBot)
{
	EcoBotReference = NewEcoBot;
}

void ACraftablePreview::Interact(AEcoBotCharacter* InteractingChar)
{
	Super::Interact(InteractingChar);
	OnBeginInteract();
	IsPlacing = IsPlacing ? false : true;
}

void ACraftablePreview::SpawnCraft()
{
	if(!EcoBotReference) return;
	
	bool bHasAllMaterials = true;
	for (const FCraftMaterialCost& MaterialCost : NeededMaterials)
	{
		int32 MaterialCount = EcoBotReference->GetInventory()->GetItemCount(MaterialCost.RequiredMaterial);
		if (MaterialCount < MaterialCost.Quantity)
		{
			bHasAllMaterials = false;
			break;
		}
	}

	if (bHasAllMaterials)
	{
		// Remove materials from inventory
		for (const FCraftMaterialCost& MaterialCost : NeededMaterials)
		{
			for (int32 i = 0; i < MaterialCost.Quantity; ++i)
			{
				EcoBotReference->GetInventory()->UseItemByClass(MaterialCost.RequiredMaterial);
			}
		}

		// Spawn the crafted item
		GetWorld()->SpawnActor<ACraftable>(CraftableToSpawn, GetActorLocation(), GetActorRotation());
		Destroy();
	}
}
