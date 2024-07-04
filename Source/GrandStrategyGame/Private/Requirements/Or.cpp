// Fill out your copyright notice in the Description page of Project Settings.


#include "Requirements/Or.h"

bool UOr::IsCompliant(UObject* Source, UObject* Target)
{
	for(URequirementComponent* Requirement : OrList)
	{
		if(IsValid(Requirement) && Requirement->IsCompliant(Source, Target))
		{
			return true;
		}
	}
	return false;
}
