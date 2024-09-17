#include "Action/GS_ActionInfo.h"
#include "Requirements/Requirement.h"

UGS_ActionInfo::UGS_ActionInfo()
{
}

UGS_ActionInstance* UGS_ActionInfo::CreateInstance(UObject* Source, UObject* Target)
{
	UGS_ActionInstance* NewInstance = NewObject<UGS_ActionInstance>(Source, InstanceClass);
	NewInstance->ActionInfo = this;
	NewInstance->Source = Source;
	NewInstance->Target = Target;
	NewInstance->Init();
	return NewInstance;
}

bool UGS_ActionInfo::FulfilsRequirements(UObject* Source, UObject* Target)
{
	for(URequirement* Requirement : Requirements)
	{
		if(IsValid(Requirement) && !Requirement->IsCompliant(Source, Target))
		{
			return false;
		}
	}
	return true;
}

UGS_ActionInstance* UGS_ActionInfo::Perform_Implementation(UObject* Source, UObject* Target, bool& Success)
{
	Success = false;
	if(!FulfilsRequirements(Source, Target)) return nullptr;

	UGS_ActionInstance* ActionInstance = CreateInstance(Source, Target);
	Success = ActionInstance->Perform();
	
	return ActionInstance;
}
