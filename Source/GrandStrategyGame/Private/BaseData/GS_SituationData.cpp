// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseData/GS_SituationData.h"
#include "Requirements/RequirementComponent.h"

UGS_SituationData::UGS_SituationData()
{
}

bool UGS_SituationData::CanOccur_Implementation(UObject* Source, UObject* Target)
{
	for(URequirementComponent* Requirement : OccurrenceRequirements)
	{
		if(IsValid(Requirement) && !Requirement->IsCompliant(Source, Target))
		{
			return false;
		}
	}
	return true;
}
