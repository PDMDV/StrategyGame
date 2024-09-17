// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GS_AttributesData.h"
#include "Engine/DataAsset.h"
#include "Goods/GS_GoodsLibrary.h"
#include "Province/GS_PopLibrary.h"
#include "GS_ProductionMethod.generated.h"

USTRUCT(BlueprintType)
struct FAffectingAttribute
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> AffectingCurve;
};

USTRUCT(BlueprintType)
struct FWorkforce
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FPop Workers;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Impact;
};

USTRUCT(BlueprintType)
struct FAttributeChange
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Change;
};

UCLASS(BlueprintType)
class GRANDSTRATEGYGAME_API UGS_ProductionMethod : public UGS_BaseObjectData
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure)
	UGameplayEffect* GetOutEffect(const UGS_AttributesData* AttributesTagsAsset);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGoodsContainer InGoods;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FWorkforce> InWorkforce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGoodsContainer OutGoods;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FAttributeChange> OutEffectAttributes;

	UPROPERTY(BlueprintReadWrite)
	UGameplayEffect* OutEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FAffectingAttribute AffectingAttributes;
};
