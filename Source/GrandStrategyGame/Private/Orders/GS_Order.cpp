// Fill out your copyright notice in the Description page of Project Settings.


#include "Orders/GS_Order.h"

bool UGS_Order::Execute_Implementation(UObject* Target)
{
	return true;
}

bool UGS_Order::Cancel_Implementation(UObject* Target)
{
	return true;
}

UWorld* UGS_Order::GetWorld() const
{
	return nullptr;
}

void UGS_Order::Finish()
{
	OnOrderFinished.Broadcast(this);
}

bool UGS_Order::TryExecute(UObject* Target)
{
	if(CanBeExecuted(Target))
	{
		return Execute(Target);
	}
	Finish();
	return false;
}

bool UGS_Order::CanBeExecuted_Implementation(UObject* Target)
{
	return true;
}
