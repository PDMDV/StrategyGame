
#include "Country\GS_Settlement.h"

#include "AbilitySystemComponent.h"
#include "AttributeSets/SettlementAttributeSet.h"

AGS_Settlement::AGS_Settlement()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<USettlementAttributeSet>(TEXT("Attribute Set"));
}

UAbilitySystemComponent* AGS_Settlement::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGS_Settlement::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(GetOwner()->GetOwner()->GetOwner(), this);
	}
}

