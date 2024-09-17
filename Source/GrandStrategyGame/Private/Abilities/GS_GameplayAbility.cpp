// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GS_GameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "BaseLibraries/GSGameplayAbilitySystemLibrary.h"

void UGS_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	for(TSubclassOf<UGameplayEffect> Effect : AbilityEffects)
	{ 
		ActiveAbilityEffects.Add(UGSGameplayAbilitySystemLibrary::ApplyEffectToTarget(Effect, GetAvatarActorFromActorInfo(), 1.0f));
	}
}

void UGS_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if(GetWorld()->bIsTearingDown) return;

	for(FActiveGameplayEffectHandle EffectHandle : ActiveAbilityEffects)
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(EffectHandle);
	}

	for(const FGameplayEventData& Event : EndAbilityEvents)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActorFromActorInfo(), Event.EventTag, Event);
	}

} 

bool UGS_GameplayAbility::CanEventActiveAbility(const FGameplayAbilityActorInfo& ActorInfo,const FGameplayEventData& Payload) const
{
	return Super::ShouldAbilityRespondToEvent(&ActorInfo, &Payload);
}
