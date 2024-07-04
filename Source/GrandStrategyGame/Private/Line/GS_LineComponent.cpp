
#include "Line\GS_LineComponent.h"

ULineComponent::ULineComponent()
{
	USceneComponent::SetMobility(EComponentMobility::Movable);
	SetGenerateOverlapEvents(false);
	UPrimitiveComponent::SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);

	CollisionType = ECollisionTraceFlag::CTF_UseDefault;
}

void ULineComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
}

void ULineComponent::Reset()
{
	GetDynamicMesh()->Reset();
}
