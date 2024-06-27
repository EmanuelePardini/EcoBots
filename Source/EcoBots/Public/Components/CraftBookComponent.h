// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Craftables/CraftBookCraftable.h"
#include "Craftables/CraftRecipe.h"
#include "CraftBookComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UCraftComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCraftComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TArray<UCraftBookCraftable*> CraftRecipes;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void AddCraftRecipe(const FCraftRecipe& NewRecipe);
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UCraftBookCraftable*> GetCraftRecipes(){return CraftRecipes;}
	//TODO: Update CraftComponent
		
};
