
#include "Managers/GS_ActionsManager.h"

class UGS_TickManager;

UGS_ActionsManager::UGS_ActionsManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGS_ActionsManager::BeginPlay()
{
	Super::BeginPlay();
}

void UGS_ActionsManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGS_ActionsManager::HandleTick(int32 Tick)
{
	/*for(FActionInstance& ActionInstance : ActionInstances)
	{
		if(ActionInstance.EndTick <= Tick)
		{
			ActionInstance.End();
			ActionInstance.Action = nullptr;
		}
	}
	Algo::RemoveIf(ActionInstances, [](const FActionInstance& ActionInstance){return ActionInstance.Action == nullptr;});*/
}

