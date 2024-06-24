#pragma once
#include "CoreMinimal.h"
#include "Components/InventoryComponent.h"
#include "CharacterData.generated.h"
class AEcoBotCharacter;

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* BodyMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* FaceMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform ActorTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HungerValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThirstValue;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// UInventoryComponent* Inventory;
};