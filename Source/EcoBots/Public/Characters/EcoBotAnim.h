// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EcoBotAnim.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UEcoBotAnim : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Grounded = true;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HasInteracted = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFlying = false;
	
	void Animate(ACharacter* Character);
	FVector GetDeltaRoot(){return ConsumeExtractedRootMotion(1).GetRootMotionTransform().GetLocation();}
};
