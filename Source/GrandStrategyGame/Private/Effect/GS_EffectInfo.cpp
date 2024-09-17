// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/GS_EffectInfo.h"


UGS_EffectInstance* UGS_EffectInfo::Apply(UObject* Source, UObject* Target, UObject* Outer, bool& Success)
{
	UGS_EffectInstance* EffectInstance = CreateEffect(Source, Target, Outer);
	Success = EffectInstance->Apply();
	return EffectInstance;
}

UGS_EffectInstance* UGS_EffectInfo::CreateEffect(UObject* Source, UObject* Target, UObject* Outer)
{
	if(!InstanceClass) return nullptr;
	
	UGS_EffectInstance* NewInstance = NewObject<UGS_EffectInstance>(Outer, InstanceClass);
	NewInstance->EffectInfo = this;
	NewInstance->Source = Source;
	NewInstance->Target = Target;
	NewInstance->Init();
	return NewInstance;
}

bool UGS_EffectInfo::IsCapable_Implementation(UObject* Source, UObject* Target, UObject* Outer)
{
	return true;
}