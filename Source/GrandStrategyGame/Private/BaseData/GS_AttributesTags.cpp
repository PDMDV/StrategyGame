// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseData/GS_AttributesTags.h"
#include "AttributeSet.h"

FGameplayAttribute UGS_AttributesTags::GetAttributeByTag(FGameplayTag Tag) const
{
	return *TagToAttributeMap.Find(Tag);
}
