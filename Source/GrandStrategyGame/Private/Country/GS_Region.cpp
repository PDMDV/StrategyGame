
#include "Country/GS_Region.h"

#include "AbilitySystemComponent.h"
#include "AttributeSets/SettlementAttributeSet.h"

AGS_Region::AGS_Region()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<USettlementAttributeSet>(TEXT("Attribute Set"));
}

UAbilitySystemComponent* AGS_Region::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGS_Region::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

