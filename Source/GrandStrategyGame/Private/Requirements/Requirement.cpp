// Fill out your copyright notice in the Description page of Project Settings.


#include "Requirements/Requirement.h"

URequirement::URequirement()
{
	
}

bool URequirement::IsCompliant_Implementation(UObject* Source, UObject* Target)
{
	return true;
}
