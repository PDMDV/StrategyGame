// Fill out your copyright notice in the Description page of Project Settings.

#include "Effect/GS_EffectInstance.h"
#include "Effect/GS_EffectInfo.h"

bool UGS_EffectInstance::Invert_Implementation()
{
	return true;
}

bool UGS_EffectInstance::End_Implementation()
{
	return true;
}

bool UGS_EffectInstance::Refresh_Implementation()
{
	return true;
}

bool UGS_EffectInstance::Apply_Implementation()
{
	return true;
}

bool UGS_EffectInstance::IsCapable_Implementation()
{
	return EffectInfo->IsCapable(Source, Target, GetOuter());
}

bool UGS_EffectInstance::Init_Implementation()
{
	return true;
}
