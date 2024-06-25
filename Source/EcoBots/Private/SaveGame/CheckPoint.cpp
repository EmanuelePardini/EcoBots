// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGame/CheckPoint.h"
#include "Characters/EcoBotCharacter.h"
#include "Characters/EcoBotController.h"
#include "Interfaces/SaveGameInterface.h"
#include "Managers/VillageSavingsManager.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/WorldCatastrophesManager.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create a collider and set it as the root component
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	SetRootComponent(Collider);
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind overlap events to the respective handlers
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnOverlapBegin);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ACheckPoint::OnOverlapEnd);
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Handler for beginning overlap event
void ACheckPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SaveData(OtherActor); // Save data when an actor begins overlapping
}

// Handler for ending overlap event
void ACheckPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SaveData(OtherActor); // Save data when an actor ends overlapping
}

// Saves data when an actor overlaps with the checkpoint
void ACheckPoint::SaveData(AActor* OtherActor)
{
	// For character data
	AEcoBotCharacter* Player = Cast<AEcoBotCharacter>(OtherActor);
	if(!Player) return;
	
	AEcoBotController* Controller = Cast<AEcoBotController>(Player->GetController());
	if(!Controller) return;

	// For level data
	AActor* VillageSavingsActor = UGameplayStatics::GetActorOfClass(GetWorld(), AVillageSavingsManager::StaticClass());
	if(!VillageSavingsActor) return;
	
	AVillageSavingsManager* VillageSavings = Cast<AVillageSavingsManager>(VillageSavingsActor);
	if(!VillageSavings) return;

	//For World Manager Data
	AActor* WorldManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AVillageSavingsManager::StaticClass());
	if(!WorldManagerActor) return;
	
	AWorldCatastrophesManager* WorldManager = Cast<AWorldCatastrophesManager>(WorldManagerActor);
	if(!WorldManager) return;

	// Send to SaveSlot
	if(GetGameInstance()->Implements<USaveGameInterface>())
	{
		ISaveGameInterface::Execute_SaveLevelData(GetGameInstance(), VillageSavings->GetLevelData(), Player->GetCharacterData(), WorldManager->GetWorldManagerData());
	}
}
