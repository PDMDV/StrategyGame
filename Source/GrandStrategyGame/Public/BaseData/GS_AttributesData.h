// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeSet.h"
#include "GS_AttributesData.generated.h"

struct FGameplayAttribute;

UENUM(BlueprintType)
enum EAttributeType
{
	Percentage UMETA(DisplayName = "Percentage"),
	Integer UMETA(DisplayName = "Integer"),
	Float UMETA(DisplayName = "Float"),
};

USTRUCT(BlueprintType)
struct FAttributeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EAttributeType> Type;
	
};

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_AttributesData : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FAttributeData> TagToAttributeMap;
	
public:
	
	UFUNCTION(BlueprintPure)
	FGameplayAttribute GetAttribute(FGameplayTag Tag) const;

	UFUNCTION(BlueprintPure)
	TEnumAsByte<EAttributeType> GetAttributeType(FGameplayTag Tag) const;

	UFUNCTION(BlueprintPure)
	FGameplayTag GetAttributeTag(const FGameplayAttribute& Attribute) const;
};
