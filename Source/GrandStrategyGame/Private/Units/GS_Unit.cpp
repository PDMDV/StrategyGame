
#include "Units/GS_Unit.h"

#include "AbilitySystemComponent.h"

AGS_Unit::AGS_Unit()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* AGS_Unit::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
 
void AGS_Unit::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AGS_Unit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

