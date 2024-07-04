#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_LineLibrary.generated.h"

USTRUCT(BlueprintType)
struct FNoisyLinePoints
{
	GENERATED_BODY()
	
	FNoisyLinePoints(const float MaxDistantRatio, const float MinSegmentLength, const int32 MaxRecursionDepth) : MaxRecursionDepth(MaxRecursionDepth), MinSegmentLength(MinSegmentLength), MaxDistantRatio(MaxDistantRatio){}
	FNoisyLinePoints(){}
	
	void Build(FVector2D A, FVector2D B, FVector2D C, FVector2D D);
	TArray<FVector2D> GetPoints();
	
	static FVector2D Interpolate(FVector2D Start, FVector2D End, double Distance);
	void Correction(FVector2D A, FVector2D& B, FVector2D C, FVector2D& D);
	void Subdivide(FVector2D A, FVector2D B, FVector2D C, FVector2D D, int32 RecursionDepth);

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector2D> Points;

	UPROPERTY(BlueprintReadOnly)
	float MinSegmentLength = 1.0f;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxRecursionDepth = 5; // 2^MaxRecursionDepth function calls

	// Maximum ratio between the distance of a new point from the original line and the length of the original line.
	UPROPERTY(BlueprintReadOnly)
	float MaxDistantRatio = 0.25; 
};


UCLASS()
class UGS_LineLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static TArray<FVector> BuildNoisyLine(FVector A, FVector B, FVector C, FVector D, float MaxDistantRatio = 0.25f, float MinSegmentLength = 1.0f, int32 MaxRecursionDepth = 5, int32 Seed = 0, bool CombineSeedWithData = true);
	
};
