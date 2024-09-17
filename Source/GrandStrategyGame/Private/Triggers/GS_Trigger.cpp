// Fill out your copyright notice in the Description page of Project Settings.


#include "Triggers/GS_Trigger.h"

#include "Action/GS_ActionInfo.h"

UGS_Trigger::UGS_Trigger()
{
	FWorldDelegates::OnPostWorldCreation.AddUObject(this, &UGS_Trigger::Start);
}

UWorld* UGS_Trigger::GetWorld() const
{
	return nullptr;
}

void UGS_Trigger::Start(UWorld* World)
{
	BeginPlay();
}

void UGS_Trigger::BeginPlay_Implementation()
{
}

bool UGS_Trigger::Register_Implementation(UObject* Object)
{
	return true;
}

bool UGS_Trigger::Triggered_Implementation(UObject* Owner, UObject* Triggerer)
{
	for(TObjectPtr<UGS_ActionInfo> Action : Actions)
	{
		bool Success;
		Action->Perform(Owner, Triggerer, Success);
	}
	return true;
}
