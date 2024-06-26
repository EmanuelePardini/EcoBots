// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InventoryItem.h"

void UInventoryItem::UseInventoryItem(AEcoBotCharacter* EcoBotCharacter)
{
	OnUseInventoryItem(EcoBotCharacter);
	
}
