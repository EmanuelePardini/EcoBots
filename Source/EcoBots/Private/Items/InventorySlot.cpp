// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InventorySlot.h"

void UInventorySlot::Init(int InitialQuantity, TSubclassOf<UInventoryItem> SlotType)
{
	//Init the slot if the Item is not already contained
	Quantity = InitialQuantity;
	Type = SlotType;
	InventoryItem = NewObject<UInventoryItem>(this, SlotType);
}
