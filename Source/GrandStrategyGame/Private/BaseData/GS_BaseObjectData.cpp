// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseData/GS_BaseObjectData.h"

UWorld* UGS_BaseObjectData::GetWorld() const
{
	return nullptr;
}

FString UGS_BaseObjectData::GetToolTipMessage_Implementation(UObject* Source, UObject* Target)
{
	return FString();
}
