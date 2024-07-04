// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/GS_Action.h"

#include "Requirements/RequirementComponent.h"

UGS_Action::UGS_Action()
{
}

UWorld* UGS_Action::GetWorld() const
{		
	return nullptr;
}

bool UGS_Action::FulfilsRequirements(UObject* Source, UObject* Target)
{
	for(URequirementComponent* Requirement : Requirements)
	{
		if(IsValid(Requirement) && !Requirement->IsCompliant(Source, Target))
		{
			return false;
		}
	}
	return true;
}

bool UGS_Action::IsCapable_Implementation(UObject* Source, UObject* Target)
{
	return true;
}

bool UGS_Action::Perform_Implementation(UObject* Source, UObject* Target)
{
	return true;
}
