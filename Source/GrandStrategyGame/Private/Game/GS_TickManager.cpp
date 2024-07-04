
#include "Game\GS_TickManager.h"

UGS_TickManager::UGS_TickManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGS_TickManager::BeginPlay()
{
	Super::BeginPlay();
}

void UGS_TickManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!IsPaused)
	{
		TimeFromLastTick += DeltaTime;
	}
	if(TimeFromLastTick > TickTime)
	{
		TimeFromLastTick = 0.0f;
		OnTick.Broadcast(++TicksNum);
	}
}

