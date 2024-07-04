// Fill out your copyright notice in the Description page of Project Settings.


#include "Requirements/RequirementComponent.h"

URequirementComponent::URequirementComponent()
{
	
}

UWorld* URequirementComponent::GetWorld() const
{
	return nullptr;
}

bool URequirementComponent::IsCompliant_Implementation(UObject* Source, UObject* Target)
{
	return true;
}
