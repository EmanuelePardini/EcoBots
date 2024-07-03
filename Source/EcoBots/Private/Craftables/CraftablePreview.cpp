// Fill out your copyright notice in the Description page of Project Settings.


#include "Craftables/CraftablePreview.h"
#include "Characters/EcoBotCharacter.h"
#include "Kismet/GameplayStatics.h"

ACraftablePreview::ACraftablePreview()
{
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>("PreviewMesh");
	PreviewMesh->SetupAttachment(RootComponent);
	ActionsWidget = CreateDefaultSubobject<UWidgetComponent>("ActionsWidget");
	ActionsWidget->SetupAttachment(PreviewMesh);
}

void ACraftablePreview::BeginPlay()
{
	Super::BeginPlay();
}

void ACraftablePreview::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (ActionsWidget) UpdateWidgetRotation();
	if(EcoBotReference) ManagePreviewPlacing();
}


void ACraftablePreview::UpdateWidgetRotation()
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
	if(IsPlacing)
	{
		FVector PlayerLocation = EcoBotReference->GetActorLocation();
		FVector ForwardVector = EcoBotReference->GetActorForwardVector();
		FVector NewLocation = PlayerLocation + (ForwardVector * 200.0f);
		SetActorLocation(NewLocation);
		
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
