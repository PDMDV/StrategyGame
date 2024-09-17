
#include "Province/Data/GS_BuildingData.h"

#include "Cost/GS_Cost.h"
#include "Effect/GS_EffectInfo.h"
#include "Requirements/Requirement.h"

UGS_BuildingData::UGS_BuildingData()
{
}

bool UGS_BuildingData::CanBeBuild(UObject* Target)
{
	for(TObjectPtr<UGS_Cost> Cost : ConstructionCosts)
	{
		if(!Cost->IsCapable(this, Target, Target))
			return false;
	}
	for(TObjectPtr<URequirement> Requirement : Requirements)
	{
		if(!Requirement->IsCompliant(this, Target))
			return false;
	}
	return true;
}
