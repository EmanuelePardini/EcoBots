// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Interactable.generated.h"
class AItem;

USTRUCT(BlueprintType)
struct FInteractionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TSubclassOf<AInteractable> ItemToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	int MaxQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	int MinQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float ItemSpawnRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	bool bToInheritRotation;
	
	FInteractionData()
		: ItemToSpawn(nullptr)
		, MaxQuantity(3)
		, MinQuantity(1)
		, ItemSpawnRadius(100)
		, bToInheritRotation(true)
	{
	}
};

UCLASS()
class ECOBOTS_API AInteractable : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TArray<FInteractionData> InteractionDatas;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float RechargeDelay = 180.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	float RechargeTimer = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	bool IsAvailable = true;
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* InteractableSound;
	UPROPERTY(EditAnywhere, Category="Sound")
	float SoundVolume = 1.f;
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundAttenuation* SoundAttenuation;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ManageRecharge(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void Interact(AEcoBotCharacter* InteractingChar  = nullptr) override;
	UFUNCTION(BlueprintCallable)
	virtual void EndInteract(AEcoBotCharacter* InteractingChar  = nullptr) override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnBeginInteract(AEcoBotCharacter* InteractingChar = nullptr);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnEndInteract(AEcoBotCharacter* InteractingChar  = nullptr);
	UFUNCTION(BlueprintCallable)
	void SpawnItem(FVector SpawnLoc = FVector(0,0,0), FRotator SpawnRot = FRotator(0,0,0));
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void NotifyAvailability();
};
