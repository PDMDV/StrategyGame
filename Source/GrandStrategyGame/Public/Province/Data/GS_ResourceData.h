// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GS_GoodData.h"
#include "GS_ResourceData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_ResourceData : public UGS_GoodData
{
	GENERATED_BODY()

public:
	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseEmergeProbability = 1.0f;
};
