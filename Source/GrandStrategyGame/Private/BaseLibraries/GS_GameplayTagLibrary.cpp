// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLibraries/GS_GameplayTagLibrary.h"

#include "GameplayTagsManager.h"

FGameplayTagContainer UGS_GameplayTagLibrary::GetAllChildren(const FGameplayTag Tag)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	return Manager.RequestGameplayTagChildren(Tag);
}

FGameplayTagContainer UGS_GameplayTagLibrary::GetAllChildrenWithDepth(FGameplayTag Tag, int32 Depth, bool OnlyExactDepth)
{
	FGameplayTagContainer Result;
	
	int32 MainTagDepth = GetNumberOfTagNodes(Tag);
	FGameplayTagContainer ChildTags = GetAllChildren(Tag);
	for(FGameplayTag ChildTag : ChildTags)
	{
		if(OnlyExactDepth)
		{
			if(GetNumberOfTagNodes(ChildTag) == MainTagDepth + Depth)
			{
				Result.AddTag(ChildTag);
			}
		}
		else
		{
			if(GetNumberOfTagNodes(ChildTag) <= MainTagDepth + Depth)
			{
				Result.AddTag(ChildTag);
			}
		}
	}
	return Result;
}

FGameplayTag UGS_GameplayTagLibrary::GetDirectParent(FGameplayTag Tag)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	return Manager.RequestGameplayTagDirectParent(Tag);
}
 
int32 UGS_GameplayTagLibrary::GetNumberOfTagNodes(FGameplayTag Tag)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	return Manager.GetNumberOfTagNodes(Tag);
}

FName UGS_GameplayTagLibrary::GetTagLastName(FGameplayTag Tag)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	
	TArray<FName> OutNames;
	Manager.SplitGameplayTagFName(Tag, OutNames);
	if(OutNames.IsEmpty())
	{
		return FName();
	}
	return OutNames.Last();
}
