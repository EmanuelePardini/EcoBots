// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/WorldCatastrophesManager.h"

// Sets default values
AWorldCatastrophesManager::AWorldCatastrophesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldCatastrophesManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldCatastrophesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

