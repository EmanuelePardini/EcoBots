// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InventorySlot.h"

void UInventorySlot::Init(int InitialQuantity, TSubclassOf<UInventoryItem> SlotType)
{
	Quantity = InitialQuantity;
	Type = SlotType;
	InventoryItem = NewObject<UInventoryItem>(this, SlotType);
}
