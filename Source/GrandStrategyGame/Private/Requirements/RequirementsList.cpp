// Fill out your copyright notice in the Description page of Project Settings.


#include "Requirements/RequirementsList.h"
#include "Requirements/RequirementComponent.h"

URequirementsList::URequirementsList()
{
}

bool URequirementsList::IsCompliant(UObject* Source, UObject* Target)
{
	for(URequirementComponent* Requirement : RequirementsList)
	{
		if(IsValid(Requirement) && !Requirement->IsCompliant(Source, Target))
		{
			return false;
		}
	}
	return true;
}
