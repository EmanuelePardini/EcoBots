// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EcoBotDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ECOBOTS_API UEcoBotDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UMaterialInterface*> EcoBotMaterials = {nullptr, nullptr};
	UPROPERTY(VisibleAnywhere)
	FTransform EcoBotTransform;

public:
	UFUNCTION(BlueprintCallable)
	TArray<UMaterialInterface*> GetEcoBotMaterials();
	UFUNCTION(BlueprintCallable)
	void SetEcoBotMaterials(UMaterialInterface* Body = nullptr, UMaterialInterface* Face = nullptr);
	UFUNCTION(BlueprintCallable)
	FTransform GetEcoBotTransform();
	UFUNCTION(BlueprintCallable)
	void SetEcoBotTransform(FTransform NewTransform);
	
};
