// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeSet.h"
#include "GS_AttributesTags.generated.h"

struct FGameplayAttribute;

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_AttributesTags : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FGameplayAttribute> TagToAttributeMap;
public:
	UFUNCTION(BlueprintPure)
	FGameplayAttribute GetAttributeByTag(FGameplayTag Tag) const;
};
