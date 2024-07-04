// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLibraries/GSGameplayAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AttributeSets/GSAttributeSet.h"
#include "BaseData/GS_AttributesTags.h"
#include "Blueprint/UserWidget.h"

FActiveGameplayEffectHandle UGSGameplayAbilitySystemLibrary::ApplyEffectToTarget(const TSubclassOf<UGameplayEffect> Effect, AActor* Target, const float Level)
{
	if (!Effect || !Target)
	{
		return FActiveGameplayEffectHandle(INDEX_NONE);
	}
	
	if(UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target))
	{
		return ApplyEffectToASC(Effect, AbilitySystemComponent, Level);
	}
	return FActiveGameplayEffectHandle(INDEX_NONE);
}

FActiveGameplayEffectHandle UGSGameplayAbilitySystemLibrary::ApplyEffectToASC(const TSubclassOf<UGameplayEffect> Effect, UAbilitySystemComponent* AbilitySystemComponent, const float Level)
{
	if (!Effect || !AbilitySystemComponent)
		return FActiveGameplayEffectHandle(INDEX_NONE);

	const FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, Level, EffectContextHandle);
	return AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

FActiveGameplayEffectHandle UGSGameplayAbilitySystemLibrary::ApplyEffectWithMagnitudeToASC(TSubclassOf<UGameplayEffect> Effect, UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag Tag, float Magnitude, float Level)
{
	if (!Effect || !AbilitySystemComponent)
		return FActiveGameplayEffectHandle(INDEX_NONE);

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, Level, EffectContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, Tag, Magnitude);
	return AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

FGameplayAttribute UGSGameplayAbilitySystemLibrary::GetAscAttributeByTag(const FGameplayTag AttributeTag, const UAbilitySystemComponent* AbilitySystemComponent)
{
	if(!AttributeTag.IsValid()) return nullptr;
	
	const UGSAttributeSet* AttributeSet = Cast<UGSAttributeSet>(AbilitySystemComponent->GetAttributeSet(UAttributeSet::StaticClass()));
	return AttributeSet->AttributesTags->GetAttributeByTag(AttributeTag);
}

float UGSGameplayAbilitySystemLibrary::GetAttributeValueByTag(const FGameplayTag AttributeTag,  const UAbilitySystemComponent* AbilitySystemComponent)
{
	const UAttributeSet* AttributeSet = AbilitySystemComponent->GetAttributeSet(UAttributeSet::StaticClass());
	const FGameplayAttribute Attribute = GetAscAttributeByTag(AttributeTag, AbilitySystemComponent);
	return Attribute.GetNumericValue(AttributeSet);
}

UAbilitySystemComponent* UGSGameplayAbilitySystemLibrary::GetControlledAbilitySystemComponent(const UUserWidget* Widget)
{
	if (const APlayerController* PlayerController = Widget->GetOwningPlayer())
	{
		return Cast<IAbilitySystemInterface>(PlayerController->GetPawn())->GetAbilitySystemComponent();
	}
	return nullptr;
}

UGameplayAbility* UGSGameplayAbilitySystemLibrary::FindAbilityWithTag(FGameplayTag Tag, UAbilitySystemComponent* AbilitySystemComponent)
{
	TArray<FGameplayAbilitySpecHandle> AbilitiesHandles;
	AbilitySystemComponent->FindAllAbilitiesWithTags(AbilitiesHandles, FGameplayTagContainer(Tag));
	if(!AbilitiesHandles.IsEmpty())
	{
		bool bIsInstanced;
		return const_cast<UGameplayAbility*>(UAbilitySystemBlueprintLibrary::GetGameplayAbilityFromSpecHandle(AbilitySystemComponent, AbilitiesHandles[0], bIsInstanced));
	}
	return nullptr;
}

void UGSGameplayAbilitySystemLibrary::GiveAbilityToActor(const TSubclassOf<UGameplayAbility> Ability, AActor* Target)
{
	if(!Target->HasAuthority()) return;

	if(UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target))
	{
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void UGSGameplayAbilitySystemLibrary::BindOnAttributeChange(const FGameplayTag AttributeTag, UAbilitySystemComponent* ASC, const TFunction<void(const FOnAttributeChangeData& ChangedAttribute)>& Functor)
{
	const FGameplayAttribute Attribute = GetAscAttributeByTag(AttributeTag, ASC);
	BindOnAttributeChange(Attribute, ASC, Functor);
}

void UGSGameplayAbilitySystemLibrary::BindOnAttributeChange(FGameplayAttribute Attribute, UAbilitySystemComponent* ASC, TFunction<void(const FOnAttributeChangeData& ChangedAttribute)> Functor)
{
	FOnGameplayAttributeValueChange& OnAttributeChangeDelegate = ASC->GetGameplayAttributeValueChangeDelegate(Attribute);
	OnAttributeChangeDelegate.AddLambda(Functor);
}