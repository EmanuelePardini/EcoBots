// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/EcoBotDataSubsystem.h"

TArray<UMaterialInterface*> UEcoBotDataSubsystem::GetEcoBotMaterials()
{
	return EcoBotMaterials;
}

void UEcoBotDataSubsystem::SetEcoBotMaterials(UMaterialInterface* Body, UMaterialInterface* Face)
{
	EcoBotMaterials[0] = Body;
	EcoBotMaterials[1] = Face;
}

FTransform UEcoBotDataSubsystem::GetEcoBotTransform()
{
	return EcoBotTransform;
}

void UEcoBotDataSubsystem::SetEcoBotTransform(FTransform NewTransform)
{
	EcoBotTransform = NewTransform;
}
