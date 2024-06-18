#pragma once
#include "CoreMinimal.h"
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
};