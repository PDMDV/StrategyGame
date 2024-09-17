
#include "Action/GS_ActionInstance.h"
#include "Action/GS_ActionInfo.h"

bool UGS_ActionInstance::Perform_Implementation()
{
	if(IsCapable())
	{
		bool Success;
		for(TObjectPtr<UGS_EffectInfo> Effect : ActionInfo->Effects)
		{
			UGS_EffectInstance* EffectInstance = Effect->Apply(Source, Target, this, Success);
			if(Success)
			{
				EffectInstances.Add(EffectInstance);
			}
			else
			{
				Cancel();
				return false;
			}
		}
		return true;
	}
	return false;
}

void UGS_ActionInstance::End_Implementation()
{
	for(UGS_EffectInstance* Effect : EffectInstances)
	{
		Effect->End();
	}
	OnActionFinished.Broadcast(this);
	MarkAsGarbage();
}

void UGS_ActionInstance::Cancel_Implementation()
{
	for(UGS_EffectInstance* Effect : EffectInstances)
	{
		Effect->Invert();
	}
	OnActionCanceled.Broadcast(this);
	MarkAsGarbage();
}

float UGS_ActionInstance::GetProgress_Implementation()
{
	return 0.0f;
}

bool UGS_ActionInstance::Init_Implementation()
{
	return true;
}

bool UGS_ActionInstance::IsCapable_Implementation()
{
	for(TObjectPtr<UGS_EffectInfo> Effect : ActionInfo->Effects)
	{
		if(!Effect->IsCapable(Source, Target, this))
		{
			return false;
		}
	}
	return ActionInfo->FulfilsRequirements(Source, Target);
}

