// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLibraries/GS_GameplayTagLibrary.h"

#include "GameplayTagsManager.h"

FGameplayTagContainer UGS_GameplayTagLibrary::GetAllChildren(const FGameplayTag Tag)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	return Manager.RequestGameplayTagChildren(Tag);
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
