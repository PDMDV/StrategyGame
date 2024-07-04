// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_BaseObjectData.h"
#include "Goods/GS_GoodsLibrary.h"
#include "GS_UnitData.generated.h"

UCLASS()
class GRANDSTRATEGYGAME_API UGS_UnitData : public UGS_BaseObjectData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGoods> RecruitmentGoods;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FGoods> UpkeepGoods;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Salary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Size = 100;
};
