// Fill out your copyright notice in the Description page of Project Settings.


#include "Requirements/GS_RequirementsData.h"

#include "Requirements/Requirement.h"

UGS_RequirementsData::UGS_RequirementsData()
{
} 

bool UGS_RequirementsData::IsCompliant(UObject* Source, UObject* Target)
{
	for(TObjectPtr<URequirement> Requirement : Requirements)
	{
		if(!Requirement->IsCompliant(Source, Target))
		{
			return false;
		}
	}
	return true;
}
