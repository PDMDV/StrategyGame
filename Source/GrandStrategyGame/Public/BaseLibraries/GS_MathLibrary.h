#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_MathLibrary.generated.h"

UCLASS()
class GRANDSTRATEGYGAME_API UGS_MathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static int32 UpperBoundInt32(const TArray<int32>& Array, int32 Value);

	UFUNCTION(BlueprintPure)
	static bool PointInTriangle(const FVector& A, const FVector& B, const FVector& C, const FVector& P, const float InsideTriangleDotProductEpsilon = 0.0f);

	UFUNCTION(BlueprintCallable)
	static TArray<FVector> ConvexHullAlgorithm(TArray<FVector> Points);

	UFUNCTION(BlueprintPure)
	static FRotator GetRotatorFromNormalKeepYaw(float Yaw, const FVector& Normal);

	UFUNCTION(BlueprintPure)
	static FVector Interpolate(const FVector& Start, const FVector& End, float Distance);

	UFUNCTION(BlueprintPure)
	static bool SegmentIntersection2D(const FVector2D& SegmentStartA, const FVector2D& SegmentEndA, const FVector2D& SegmentStartB, const FVector2D& SegmentEndB, FVector2D& IntersectionPoint);

	UFUNCTION(BlueprintPure)
	static TArray<FVector> Intersection(const TArray<FVector>& Array1, const TArray<FVector>& Array2);

	UFUNCTION(BlueprintPure)
	static FVector GetTriangleNormal(FVector A, FVector B, FVector C);
 
	UFUNCTION(BlueprintPure)
	static float GetPointDistanceToSegment(FVector2D Point, FVector2D SegmentStart, FVector2D SegmentEnd);

	UFUNCTION(BlueprintPure)
	static TArray<FVector2D> GetRandomPointsInRadius(FVector2D Center, int32 Number, float MaxRadius, float MinRadius);
	
	UFUNCTION(BlueprintPure)
	static TArray<FVector2D> ShrinkPolygonByOffset(const TArray<FVector2D>& Points, float Offset);
	
	UFUNCTION(BlueprintPure)
	static TArray<FVector2D> PolygonsOffset(const TArray<FVector2D>& Points, float Offset);

	UFUNCTION(BlueprintPure)
	static float ConvertPercentage(const float Percentage, const int32 Times);

	UFUNCTION(BlueprintPure)
	static void GetPolygonBounds(const TArray<FVector2D>& Polygon,  FVector2D& Min,  FVector2D& Max);

	UFUNCTION(BlueprintPure)
	static TArray<FVector2D> GetRandomPointsInsidePolygon(const TArray<FVector2D>& Polygon, int32 PointsNumber);

	// TO DO this function doesnt work. Can be removed
	UFUNCTION(BlueprintPure)
	static int32 GetRandomNumberWithAverage(float Average, int32 Max);
};
