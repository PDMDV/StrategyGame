// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GSGameplayAbilitySystemLibrary.generated.h" 

class UGameplayAbility;
struct FOnAttributeChangeData;
struct FGameplayAttribute;
struct FGameplayTag;
class UAbilitySystemComponent;
class UGameplayEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTest, const FGameplayTag, Tag, int, Number);

UCLASS()
class GRANDSTRATEGYGAME_API UGSGameplayAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static FActiveGameplayEffectHandle ApplyEffectToTarget(TSubclassOf<UGameplayEffect> Effect, AActor* Target, float Level);

	UFUNCTION(BlueprintCallable)
	static FActiveGameplayEffectHandle ApplyEffectToASC(TSubclassOf<UGameplayEffect> Effect, UAbilitySystemComponent* AbilitySystemComponent, float Level = 0.f);

	UFUNCTION(BlueprintCallable)
	static FActiveGameplayEffectHandle ApplyEffectWithMagnitudeToASC(TSubclassOf<UGameplayEffect> Effect, UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag Tag, float Magnitude = 0.f, float Level = 0.f);
	
	UFUNCTION(BlueprintPure)
	static FGameplayAttribute GetAscAttributeByTag(const FGameplayTag AttributeTag, const UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintPure)
	static float GetAttributeValueByTag(FGameplayTag AttributeTag,  const UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintPure)
	static UAbilitySystemComponent* GetControlledAbilitySystemComponent(const UUserWidget* Widget);

	UFUNCTION(BlueprintPure)
	static UGameplayAbility* FindAbilityWithTag(FGameplayTag Tag, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable)
	static void GiveAbilityToActor(TSubclassOf<UGameplayAbility> Ability, AActor* Target);
	
	static void BindOnAttributeChange(FGameplayTag AttributeTag, UAbilitySystemComponent* ASC, const TFunction<void(const FOnAttributeChangeData& ChangedAttribute)>& Functor);
	static void BindOnAttributeChange(FGameplayAttribute Attribute, UAbilitySystemComponent* ASC, TFunction<void(const FOnAttributeChangeData& ChangedAttribute)> Functor);
	
};
