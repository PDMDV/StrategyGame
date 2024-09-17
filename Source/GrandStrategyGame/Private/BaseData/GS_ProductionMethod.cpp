// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseData/GS_ProductionMethod.h"

#include "BaseLibraries/GSGameplayAbilitySystemLibrary.h"

UGameplayEffect* UGS_ProductionMethod::GetOutEffect(const UGS_AttributesData* AttributesTagsAsset)
{
	if(!OutEffect)
	{
		TArray<FGameplayTag> AttributeTags;
		for(FAttributeChange Attribute : OutEffectAttributes)
		{
			AttributeTags.Add(Attribute.AttributeTag);
		}
		OutEffect = UGSGameplayAbilitySystemLibrary::CreateEffectFromTags(AttributeTags, FName(GetName() + "_Effect"), AttributesTagsAsset);
	}
	return OutEffect;
}
