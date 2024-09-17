#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_PointsManipulationLibrary.generated.h"

struct FCellInfo;

UCLASS()
class GRANDSTRATEGYGAME_API UGS_PointsManipulationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static void MoreEvenlyDistributePoints(UPARAM(ref) TArray<FVector>& Points, const FBox& BoundsIn, const float Strength = 1.0);

	UFUNCTION(BlueprintCallable)
	static void MoreEvenlyDistributeCells(UPARAM(ref) TArray<FCellInfo>& CellPoints, const FBox& BoundsIn, const float Strength = 1.0);
	
};
