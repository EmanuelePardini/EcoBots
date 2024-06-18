// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EcoBotAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEcoBotAnim::Animate(ACharacter* Character)
{
		//Update the parameters based on the character movement
		Grounded = !Character->GetCharacterMovement()->IsFalling();
		Speed = Character->GetCharacterMovement()->Velocity.Size();
	
}
