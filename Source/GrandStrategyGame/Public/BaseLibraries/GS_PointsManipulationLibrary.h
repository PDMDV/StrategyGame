// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_PointsManipulationLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GRANDSTRATEGYGAME_API UGS_PointsManipulationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static void MoreEvenlyDistributePoints(UPARAM(ref) TArray<FVector>& Points, const FBox& BoundsIn, const float Strength = 1.0);
	
};
