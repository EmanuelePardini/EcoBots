// Fill out your copyright notice in the Description page of Project Settings.


#include "Craftables/CraftRecipe.h"

void UCraftRecipe::UseRecipe()
{
	OnRecipeUse.Broadcast(this);
	OnUseRecipe();
}
