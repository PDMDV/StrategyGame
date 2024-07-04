		
#include "Line\GS_LineLibrary.h"

#include "BaseLibraries\GS_ArrayLibrary.h"
#include "BaseLibraries\GS_MathLibrary.h"

FVector2D FNoisyLinePoints::Interpolate(FVector2D Start, FVector2D End, double Distance)
{
 	return FMath::Vector2DInterpTo(Start, End, Distance, 1.0f);
}

void FNoisyLinePoints::Correction(FVector2D A, FVector2D& B, FVector2D C, FVector2D& D)
{
 	FVector2D AC = A - C;
 	FVector2D Perpendicular1 = FVector2D{-AC.Y, AC.X};
 	FVector2D Perpendicular2 = FVector2D{AC.Y, -AC.X};
 	Perpendicular1 *= 10000;
	Perpendicular2 *= 10000;
	Perpendicular1 += A;
 	Perpendicular2 += A;

 	FVector2D BC_Intersection;
 	if(UGS_MathLibrary::SegmentIntersection2D( Perpendicular1,Perpendicular2,B, C,BC_Intersection))
 	{
 		B = BC_Intersection;
 	}
 	
 	FVector2D CD_Intersection;
 	if(UGS_MathLibrary::SegmentIntersection2D( Perpendicular1,Perpendicular2,C, D,CD_Intersection))
 	{
	 	D = CD_Intersection;
 	}
}

void FNoisyLinePoints::Subdivide(FVector2D A, FVector2D B, FVector2D C, FVector2D D, int32 RecursionDepth)
{
 	if(RecursionDepth > MaxRecursionDepth) return;
	if((FVector2D::Distance(A,C) * 2) < MinSegmentLength) return;
 	
 	// The correction truncates the shape so that it does not have concave interior angles because the algorithm does not work when such angles are present.
	Correction(A, B, C, D);
 	Correction(C, B, A, D);
		
 	const FVector2D AC = Interpolate(A,C, 0.5);
		
 	const FVector2D AB = Interpolate(A,B, 0.5);
 	const FVector2D BC = Interpolate(B,C, 0.5);
 	const FVector2D CD = Interpolate(C,D, 0.5);
 	const FVector2D AD = Interpolate(D,A, 0.5);

    const FVector2D TargetPoint = FMath::RandBool() ? D : B;
    const float DistanceToBaseLine = UGS_MathLibrary::GetPointDistanceToSegment(TargetPoint,A,C);
    const float MaxInterpolationDistance = 1 / (DistanceToBaseLine / FVector2D::Distance(A,C) / MaxDistantRatio);
 	
 	const double InterpolateDistance = FMath::RandRange(0.0,FMath::Min(MaxInterpolationDistance,0.9));
 	const FVector2D Center = Interpolate(AC,TargetPoint, InterpolateDistance);
		
 	Subdivide(A,AB,Center,AD, RecursionDepth+1);
 	Points.Push(Center);
 	Subdivide(Center,BC,C,CD, RecursionDepth+1);
}

void FNoisyLinePoints::Build(FVector2D A, FVector2D B, FVector2D C, FVector2D D)
{
 	Points.Push(A);
	Subdivide(A,B,C,D, 0);
	Points.Push(C);
}

TArray<FVector2D> FNoisyLinePoints::GetPoints()
{
 	return Points;
}

TArray<FVector> UGS_LineLibrary::BuildNoisyLine(FVector A, FVector B, FVector C, FVector D, float MaxDistantRatio, float MinSegmentLength, int32 MaxRecursionDepth, int32 Seed, bool CombineSeedWithData)
{
	if(CombineSeedWithData)
	{
		const int32 CombinedDataHash = GetTypeHash(FIntVector2(A.X, A.Y)) + GetTypeHash(FIntVector2(B.X, B.Y)) + GetTypeHash(FIntVector2(C.X, C.Y)) + GetTypeHash(FIntVector2(D.X,D.Y));
		FMath::RandInit(Seed + CombinedDataHash);
	}
	else
	{
		FMath::RandInit(Seed);
	}
	FNoisyLinePoints NoisyLine(MaxDistantRatio, MinSegmentLength, MaxRecursionDepth);
	NoisyLine.Build(FVector2D(A),FVector2D(B),FVector2D(C),FVector2D(D));
	return UGS_ArrayLibrary::ConvertToVector(NoisyLine.GetPoints());
}
