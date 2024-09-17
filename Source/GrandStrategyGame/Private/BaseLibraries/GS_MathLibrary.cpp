
#include "BaseLibraries/GS_MathLibrary.h"

#include "GeomTools.h"
#include "Algo/MaxElement.h"
#include "Curve/PolygonOffsetUtils.h"
#include "Field/FieldSystemNodes.h"
#include "Kismet/KismetMathLibrary.h"

FVector UGS_MathLibrary::Interpolate(const FVector& Start, const FVector& End, float Distance)
{
	return FMath::VInterpTo(Start, End, Distance, 1.0f);
}

bool UGS_MathLibrary::SegmentIntersection2D(const FVector2D& SegmentStartA, const FVector2D& SegmentEndA, const FVector2D& SegmentStartB, const FVector2D& SegmentEndB, FVector2D& IntersectionPoint)
{
	FVector Intersection;
	const bool Success = FMath::SegmentIntersection2D(
	FVector(SegmentStartA,0),
	FVector(SegmentEndA,0),
	FVector(SegmentStartB,0),
	FVector(SegmentEndB,0),
	Intersection);
	
	IntersectionPoint = {Intersection.X,Intersection.Y};
	return Success;
}

TArray<FVector> UGS_MathLibrary:: Intersection(const TArray<FVector>& Array1, const TArray<FVector>& Array2)
{
	TArray<FVector> Result;
	for(auto Element : Array1)
	{
		if(Array2.Find(Element) != INDEX_NONE)
		{
			Result.Push(Element);
		}
	}
	return Result;
}

int32 UGS_MathLibrary::UpperBoundInt32(const TArray<int32>& Array, int32 Value)
{
	return Algo::UpperBound(Array,Value);
}

bool UGS_MathLibrary::PointInTriangle(const FVector& A, const FVector& B, const FVector& C, const FVector& P, const float InsideTriangleDotProductEpsilon)
{
	// Check if the triangle is correct
	if(FMath::IsNearlyZero(FVector::Triple(B - A, C - A, FVector::CrossProduct(B - A, C - A))))
	{
		return false;
	}
	return FGeomTools::PointInTriangle(FVector3f(A), FVector3f(B), FVector3f(C), FVector3f(P), InsideTriangleDotProductEpsilon);
}

TArray<FVector> UGS_MathLibrary::ConvexHullAlgorithm(TArray<FVector> Points)
{
	TArray<int32> Indexes;
	ConvexHull2D::ComputeConvexHull(Points,Indexes);
	TArray<FVector> Result;
	for(const int32 Index : Indexes)
	{
		Result.Add(Points[Index]);
	}
	return Result;
}

FRotator UGS_MathLibrary::GetRotatorFromNormalKeepYaw(float Yaw, const FVector& Normal)
{
	typedef UKismetMathLibrary Lib;
	
	const FVector UpVector = {0, 0, 1};
	const FVector InVect = Lib::GetForwardVector({0.0f,Yaw,0.f});
	const float Angle = Lib::DegAcos(Lib::Dot_VectorVector(Normal, UpVector)) * -1.0f;
	const FVector Axis = FVector::CrossProduct(Normal, UpVector).GetSafeNormal();
	const FVector Rotated = Lib::RotateAngleAxis(InVect, Angle, Axis);

	FRotator Result = Lib::MakeRotFromZX(Normal, Rotated);
	Result.Yaw = Yaw;
	return Result;
}

FVector UGS_MathLibrary::GetTriangleNormal(FVector A, FVector B, FVector C)
{
	return FVector::CrossProduct(A - B, A - C);
}

float UGS_MathLibrary::GetPointDistanceToSegment(FVector2D Point, FVector2D SegmentStart, FVector2D SegmentEnd)
{
	return UKismetMathLibrary::GetPointDistanceToSegment(FVector(Point,0),FVector(SegmentStart,0),FVector(SegmentEnd,0));
}

TArray<FVector2D> UGS_MathLibrary::GetRandomPointsInRadius(FVector2D Center, int32 Number, float MaxRadius, float MinRadius)
{
	if(MaxRadius <= MinRadius)
	{
		UE_LOG(LogTemp, Error, TEXT("GetRandomPointsInRadius has incorrect arguments"));
		return {};
	}
	
	TArray<FVector2D> Result;
	while (Result.Num() < Number)
	{
		float X = FMath::FRandRange(-MaxRadius,MaxRadius);
		float Y = FMath::FRandRange(-MaxRadius,MaxRadius);
		
		FVector2D RandomPoint(X, Y);
		const float Length = RandomPoint.Length();
		if ( Length <= MaxRadius && Length >= MinRadius)
		{
			Result.Add(RandomPoint + Center);
		}
	}
	
	return Result;
}

TArray<FVector2D> UGS_MathLibrary::ShrinkPolygonByOffset(const TArray<FVector2D>& Points, const float Offset)
{
	TArray<FVector2D> Result;
	
	for (int32 i = 0; i < Points.Num(); ++i)
	{
		const FVector2D CurrentPoint = Points[i];
		const FVector2D PreviousPoint = (i == 0) ? Points.Last() : Points[(i - 1)];
		const FVector2D NextPoint = (i == Points.Num() - 1) ? Points[0] : Points[i + 1]; 
		
		FVector2D Bisector = FMath::Vector2DInterpTo((PreviousPoint - CurrentPoint).GetSafeNormal(),(NextPoint - CurrentPoint).GetSafeNormal(), 0.5f, 1.0f).GetSafeNormal();
		
		if(Bisector == FVector2D{0,0})
		{
			Bisector = FVector2D(PreviousPoint.Y - CurrentPoint.Y,PreviousPoint.X - CurrentPoint.X).GetSafeNormal();
		}
		
		if(FGeomTools2D::IsPointInPolygon(CurrentPoint + Bisector , Points))
		{
			Result.Add(CurrentPoint + (Bisector * Offset));
		}
		else
		{
			Result.Add(CurrentPoint + (Bisector * -Offset));
		}
	}
	return Result;
}

TArray<FVector2D> UGS_MathLibrary::PolygonsOffset(const TArray<FVector2D>& Points, float Offset)
{
	using namespace UE::Geometry;
	
	TArray<FGeneralPolygon2d> In{FGeneralPolygon2d(Points)};
	TArray<FGeneralPolygon2d> Out;
	
	UE::Geometry::PolygonsOffset(Offset, In, Out, true, 2);
	TArray<FVector2D> Result;
	if(Out.Num() > 0)
	{
		FGeneralPolygon2d* Longest = Algo::MaxElement(Out, [&](const FGeneralPolygon2d& A, const FGeneralPolygon2d& B)
		{
			return A.GetOuter().GetVertices().Num() < B.GetOuter().GetVertices().Num();
		});
		Result = Longest->GetOuter().GetVertices();
	}
	return Result;
}

float UGS_MathLibrary::ConvertPercentage(const float Percentage, const int32 Times)
{
	return FMath::Pow(1.f + Percentage, 1.f/Times) - 1.f;
}

void UGS_MathLibrary::GetPolygonBounds(const TArray<FVector2D>& Polygon,  FVector2D& Min,  FVector2D& Max)
{
	if (Polygon.Num() == 0) return;
	
	Min = Polygon[0];
	Max = Polygon[0];
	for (const FVector2D& Vertex : Polygon)
	{
		if (Vertex.X < Min.X) Min.X = Vertex.X;
		if (Vertex.Y < Min.Y) Min.Y = Vertex.Y;
		if (Vertex.X > Max.X) Max.X = Vertex.X;
		if (Vertex.Y > Max.Y) Max.Y = Vertex.Y;
	}
}

TArray<FVector2D> UGS_MathLibrary::GetRandomPointsInsidePolygon(const TArray<FVector2D>& Polygon, const int32 PointsNumber)
{
	TArray<FVector2D> Result;
	FVector2D Min, Max;
	GetPolygonBounds(Polygon, Min, Max);

	for(int32 i = 0 ; i < PointsNumber ; i++)
	{
		while(true)
		{
			FVector2D Point = FVector2D(FMath::FRandRange(Min.X, Max.X),
										FMath::FRandRange(Min.Y, Max.Y));
			if(FGeomTools2D::IsPointInPolygon(Point, Polygon))
			{
				Result.Add(Point);
				break;
			}
		}
	}
	return Result;
}

int32 UGS_MathLibrary::GetRandomNumberWithAverage(float Average, int32 Max)
{
	int32 Result = 0;
	float X = Average / static_cast<float>(Max);
	for(int i = 0 ; i < Max; i++)
	{
		if( FMath::FRand() <= X )
		{
			Result++;
		}
	}
	return Result;
}
