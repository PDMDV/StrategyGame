
#include "Map/MapObject.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseLibraries/GS_Library.h"
#include "Game/GS_GameState.h"

AMapObject::AMapObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMapObject::AnnounceProvinceChange()
{
	AGS_GameState* GameState = UGS_Library::GetGSGameState(this);
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.EventMagnitude = ProvinceID;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GameState, FGameplayTag::RequestGameplayTag("Event.ObjectEnteredProvince"), Data);
}

void AMapObject::ChangeProvince(int32 NewProvinceID)
{
	int32 OldProvinceID = ProvinceID;
	ProvinceID = NewProvinceID;
	AnnounceProvinceChange();
	OnProvinceChanged.Broadcast(OldProvinceID, NewProvinceID);
}

void AMapObject::SetFogged(bool IsFogged)
{
	if(VisibilityType == EVisibilityType::Fogged)
	{
		GetRootComponent()->SetVisibility(!IsFogged,true);
	}
}

void AMapObject::InitVisibility()
{
	if(VisibilityType == EVisibilityType::AlwaysVisible)
	{
		GetRootComponent()->SetVisibility(true ,true);
	}
	if(VisibilityType == EVisibilityType::AlwaysInvisible)
	{
		GetRootComponent()->SetVisibility(false,true);
	}
}

void AMapObject::BeginPlay()
{
	Super::BeginPlay();
	
	ChangeProvince(ProvinceID);
	InitVisibility();
}

void AMapObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



