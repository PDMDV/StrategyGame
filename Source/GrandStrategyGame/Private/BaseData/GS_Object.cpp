// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseData/GS_Object.h"

UWorld* UGS_Object::GetWorld() const
{
	return nullptr;
}

FString UGS_Object::GetToolTipMessage_Implementation(UObject* Source, UObject* Target)
{
	return FString();
}

