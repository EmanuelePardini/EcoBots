// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Craftables/CraftBookCraftable.h"
#include "CraftBookComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UCraftBookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCraftBookComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TArray<UCraftBookCraftable*> CraftRecipes;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void Init();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//TODO: Update CraftComponent
		
};
