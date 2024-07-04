// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_ArmyUnitLibrary.generated.h"

class UGS_UnitData;

USTRUCT(BlueprintType)
struct FArmyUnit
{
	GENERATED_BODY()

	FArmyUnit() {};
	FArmyUnit(const TObjectPtr<UGS_UnitData>& UnitData) : UnitData(UnitData){};

	friend bool operator==(const FArmyUnit& Lhs, const FArmyUnit& RHS)
	{
		return Lhs.UnitData == RHS.UnitData;
	}

	friend bool operator!=(const FArmyUnit& Lhs, const FArmyUnit& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGS_UnitData> UnitData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount = 0;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_ArmyUnitLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
