// Fill out your copyright notice in the Description page of Project Settings.


#include "Cost/GS_Cost.h"

UGS_Cost::UGS_Cost()
{
}


bool UGS_Cost::CanAffordCost_Implementation(UObject* Payer, UObject* Causer)
{
	return true;
}

bool UGS_Cost::Pay_Implementation(UObject* Payer, UObject* Causer)
{
	return true;
}

UWorld* UGS_Cost::GetWorld() const
{
	return nullptr;
}
