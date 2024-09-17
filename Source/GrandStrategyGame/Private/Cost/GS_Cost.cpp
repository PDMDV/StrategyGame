// Fill out your copyright notice in the Description page of Project Settings.


#include "Cost/GS_Cost.h"

UGS_Cost::UGS_Cost()
{
}

bool UGS_Cost::IsCapable_Implementation(UObject* Source, UObject* Target, UObject* Outer)
{
	return Super::IsCapable_Implementation(Source, Target, Outer);
}
