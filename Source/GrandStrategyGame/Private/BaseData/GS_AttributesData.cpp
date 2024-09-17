// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseData/GS_AttributesData.h"
#include "AttributeSet.h"

FGameplayAttribute UGS_AttributesData::GetAttribute(FGameplayTag Tag) const
{
	return (TagToAttributeMap.Find(Tag))->Attribute;
}

TEnumAsByte<EAttributeType> UGS_AttributesData::GetAttributeType(FGameplayTag Tag) const
{
	return TagToAttributeMap.Find(Tag)->Type;
}

FGameplayTag UGS_AttributesData::GetAttributeTag(const FGameplayAttribute& Attribute) const
{
	for(auto Pair : TagToAttributeMap.Array())
	{
		if(Pair.Value.Attribute == Attribute)
		{
			return Pair.Key;
		}
	}
	return FGameplayTag::EmptyTag;
}
