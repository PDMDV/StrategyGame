// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GS_GameplayAbility.generated.h"

UCLASS()
class GRANDSTRATEGYGAME_API UGS_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintPure)
	bool CanEventActiveAbility(const FGameplayAbilityActorInfo& ActorInfo, const FGameplayEventData& Payload) const;

	
	UPROPERTY(EditDefaultsOnly, Category = Effects, meta=(Categories="Ability Effects"))
	TArray<TSubclassOf<UGameplayEffect>> AbilityEffects;

	UPROPERTY(EditDefaultsOnly, Category = Events, meta=(Categories="End Ability Events"))
	TArray<FGameplayEventData> EndAbilityEvents;

	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> ActiveAbilityEffects;


};
