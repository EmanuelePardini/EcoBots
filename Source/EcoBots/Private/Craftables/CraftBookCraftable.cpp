// Fill out your copyright notice in the Description page of Project Settings.


#include "Craftables/CraftBookCraftable.h"

void UCraftBookCraftable::UnlockRecipe(int Quantity)
{
	if(Quantity >= CraftRecipe.UnlockCost)
	{
		CraftRecipe.Unlocked = true;
	}
	
}
