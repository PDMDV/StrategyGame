// Fill out your copyright notice in the Description page of Project Settings.


#include "Missions/GS_MissionData.h"

bool UGS_MissionData::IsCapable_Implementation(UObject* Source, UObject* Target)
{
	for(URequirement* Objective : Objectives)
	{
		if(IsValid(Objective) && !Objective->IsCompliant(Source, Target))
		{
			return false;
		}
	}
	return true;
}

bool UGS_MissionData::ApplyRewards_Implementation(UObject* Source, UObject* Target)
{
	for(TObjectPtr<UGS_EffectInfo> Reward : Rewards)
	{
		bool Success;
		Reward->Apply(Source,Target, this, Success);
	}
	return true;
}
