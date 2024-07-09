#pragma once

#include "CoreMinimal.h"
#include "Stat.h"
#include "Components/ActorComponent.h"
#include "EcoBotStatsComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOBOTS_API UEcoBotStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEcoBotStatsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStat HealthStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStat HungerStat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStat ThirstStat;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnValueChanged, float, HealthPercent, float, HungerPercent, float, ThirstPercent);
	FOnValueChanged OnValueChanged;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthFinished);
	FOnHealthFinished OnHealthFinished;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void IncrementHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void IncrementHunger(float Amount);

	UFUNCTION(BlueprintCallable)
	void IncrementThirst(float Amount);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_IncrementHealth(float Amount);
	bool Server_IncrementHealth_Validate(float Amount);
	void Server_IncrementHealth_Implementation(float Amount);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_IncrementHunger(float Amount);
	bool Server_IncrementHunger_Validate(float Amount);
	void Server_IncrementHunger_Implementation(float Amount);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_IncrementThirst(float Amount);
	bool Server_IncrementThirst_Validate(float Amount);
	void Server_IncrementThirst_Implementation(float Amount);

	UFUNCTION(BlueprintCallable)
	void ManageStatsTimer(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void ManageHealthTimer(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void ManageHungerTimer(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void ManageThirstTimer(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateHunger(float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateThirst(float Value);

	UFUNCTION(BlueprintCallable)
	void Die();
};
