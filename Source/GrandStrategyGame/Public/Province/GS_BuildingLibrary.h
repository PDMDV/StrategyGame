// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_BuildingLibrary.generated.h"

class UGS_BuildingData;

USTRUCT(BlueprintType)
struct FBuilding
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGS_BuildingData> BuildingData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Efficiency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mark = 0;
	
};
UCLASS()
class GRANDSTRATEGYGAME_API UGS_BuildingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
