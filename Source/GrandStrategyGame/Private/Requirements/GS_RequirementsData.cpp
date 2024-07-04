// Fill out your copyright notice in the Description page of Project Settings.


#include "Requirements/GS_RequirementsData.h"

UGS_RequirementsData::UGS_RequirementsData()
{
	RequirementsList = CreateDefaultSubobject<URequirementsList>(TEXT("Requirements List"));
}

bool UGS_RequirementsData::IsCompliant(UObject* Source, UObject* Target)
{
	return RequirementsList->IsCompliant(Source, Target);
}
