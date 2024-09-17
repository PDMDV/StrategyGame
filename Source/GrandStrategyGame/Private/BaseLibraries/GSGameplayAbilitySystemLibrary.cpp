// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLibraries/GSGameplayAbilitySystemLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AttributeSets/GSAttributeSet.h"
#include "BaseData/GS_AttributesData.h"
#include "Blueprint/UserWidget.h"

int UGSGameplayAbilitySystemLibrary::SendGameplayEventToActor(AActor* Actor, FGameplayTag EventTag, FGameplayEventData Payload)
{
	if (::IsValid(Actor))
	{
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
		if (AbilitySystemComponent != nullptr && IsValidChecked(AbilitySystemComponent))
		{
			FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
			return AbilitySystemComponent->HandleGameplayEvent(EventTag, &Payload);
		}
	}
	return 0;
}

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

FActiveGameplayEffectHandle UGSGameplayAbilitySystemLibrary::ApplyRawEffectToTarget(UGameplayEffect* Effect, AActor* Target, float Level)
{
	if (!Effect || !Target)
	{
		return FActiveGameplayEffectHandle(INDEX_NONE);
	}
	
	if(UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target))
	{
		FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
		return AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect, Level, Context);
	}
	return FActiveGameplayEffectHandle(INDEX_NONE);
}

UGameplayEffect* UGSGameplayAbilitySystemLibrary::CreateEffectFromTags(TArray<FGameplayTag> AttributesTags, FName Name, const UGS_AttributesData* AttributesTagsAsset, EGameplayEffectDurationType DurationType)
{
	UGameplayEffect* GameplayEffect = NewObject<UGameplayEffect>(GetTransientPackage(), Name);
	GameplayEffect->DurationPolicy = DurationType;

	for(FGameplayTag AttributeTag : AttributesTags)
	{
		FGameplayModifierInfo AttributeModifier;
		AttributeModifier.Attribute = AttributesTagsAsset->GetAttribute(AttributeTag);
		FSetByCallerFloat SetByCallerFloat;
		SetByCallerFloat.DataTag = AttributeTag;
		AttributeModifier.ModifierMagnitude = FGameplayEffectModifierMagnitude(SetByCallerFloat);
		GameplayEffect->Modifiers.Add(AttributeModifier);
	}

	return GameplayEffect;
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
	if(AttributeSet)
	{
		return AttributeSet->AttributesTags->GetAttribute(AttributeTag);
	}
	return FGameplayAttribute();
}

float UGSGameplayAbilitySystemLibrary::GetAttributeValueByTag(const FGameplayTag AttributeTag,  const UAbilitySystemComponent* AbilitySystemComponent)
{
	const UAttributeSet* AttributeSet = AbilitySystemComponent->GetAttributeSet(UAttributeSet::StaticClass());
	const FGameplayAttribute Attribute = GetAscAttributeByTag(AttributeTag, AbilitySystemComponent);
	if(Attribute.IsValid())
	{
		return Attribute.GetNumericValue(AttributeSet);
	}
	else
	{
		return 0.0f;
	}
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

bool UGSGameplayAbilitySystemLibrary::RemoveEffectWithTag(FGameplayTag Tag, UAbilitySystemComponent* AbilitySystemComponent, int32 StacksToRemove)
{
	if(!AbilitySystemComponent) return false;
	
	TArray<FActiveGameplayEffectHandle> Effects = AbilitySystemComponent->GetActiveEffectsWithAllTags(Tag.GetSingleTagContainer());
	if(!Effects.IsEmpty())
	{
		return AbilitySystemComponent->RemoveActiveGameplayEffect(Effects[0], StacksToRemove);
	}
	return false;
}

bool UGSGameplayAbilitySystemLibrary::RemoveEffectWithClass(TSubclassOf<UGameplayEffect> Class, UAbilitySystemComponent* AbilitySystemComponent, int32 StacksToRemove)
{
	if(!AbilitySystemComponent) return false;

	FGameplayEffectQuery Query;
	Query.EffectDefinition = Class;
	TArray<FActiveGameplayEffectHandle> Effects = AbilitySystemComponent->GetActiveEffects(Query);
	if(!Effects.IsEmpty())
	{
		return AbilitySystemComponent->RemoveActiveGameplayEffect(Effects[0], StacksToRemove);
	}
	return false;
}

void UGSGameplayAbilitySystemLibrary::ApplyOrUpdateGameplayEffect(TSubclassOf<UGameplayEffect> Class, UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag Tag, float Magnitude)
{
	FGameplayEffectQuery Query;
	Query.EffectDefinition = Class;
	TArray<FActiveGameplayEffectHandle> EffectHandles = AbilitySystemComponent->GetActiveEffects(Query);
	if(EffectHandles.IsEmpty())
	{
		ApplyEffectWithMagnitudeToASC(Class, AbilitySystemComponent, Tag, Magnitude);
	}
	else
	{
		for(const FActiveGameplayEffectHandle EffectHandle : EffectHandles)
		{
			AbilitySystemComponent->UpdateActiveGameplayEffectSetByCallerMagnitude(EffectHandle, Tag, Magnitude);
		}
	}
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

FGameplayAbilityActorInfo UGSGameplayAbilitySystemLibrary::GetActorInfo(UAbilitySystemComponent* ASC)
{
	return *ASC->AbilityActorInfo;
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