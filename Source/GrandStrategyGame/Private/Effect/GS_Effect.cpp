// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/GS_Effect.h"

#include "BaseLibraries/GSGameplayAbilitySystemLibrary.h"

UWorld* UGS_Effect::GetWorld() const
{
	return UObject::GetWorld();
}

void UGS_Effect::ApplyGameplayEffects(UObject* Source, UObject* Target)
{
	if(IsCapable(Source, Target))
	{
		for(const TSubclassOf<UGameplayEffect> Effect : Effects)
		{
			if(AActor* TargetActor = Cast<AActor>(Target))
			{
				UGSGameplayAbilitySystemLibrary::ApplyEffectToTarget(Effect, TargetActor, 1.0f);
			}
		}
	}
}

bool UGS_Effect::IsCapable_Implementation(UObject* Source, UObject* Target)
{
	return true;
}

void UGS_Effect::Apply_Implementation(UObject* Source, UObject* Target)
{
	ApplyGameplayEffects(Source, Target);
}
