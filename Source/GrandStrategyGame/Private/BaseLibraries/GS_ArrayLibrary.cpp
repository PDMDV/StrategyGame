
#include "BaseLibraries/GS_ArrayLibrary.h"

#include "Algo/Accumulate.h"

TArray<FVector> UGS_ArrayLibrary::ConvertToVector(TArray<FVector2D> Points)
{
	TArray<FVector> Result;
	for(auto Point : Points)
	{
		Result.Add({Point.X, Point.Y, 0});
	}
	return Result;
}

FVector UGS_ArrayLibrary::GetCenterOfPoints(const TArray<FVector>& Points)
{
	// This formula is not entirely correct but is sufficient
	const FVector Sum = Algo::Accumulate(Points, FVector(0,0,0));;
	return Sum / Points.Num();
}

TArray<FVector2D> UGS_ArrayLibrary::ConvertToVector2D(TArray<FVector> Points)
{
	TArray<FVector2D> Result;
	for(auto Point : Points)
	{
		Result.Add({Point.X, Point.Y});
	}
	return Result;
}

void UGS_ArrayLibrary::AddToAll(TArray<FVector>& Array, FVector Value)
{
	for(FVector& Element : Array)
	{
		Element += Value;
	}
}

int32 UGS_ArrayLibrary::FindVectorIgnoringAxis(const TArray<FVector>& Array, FVector Value, bool IgnoreX, bool IgnoreY, bool IgnoreZ)
{
	int32 Index = 0;
	for(const FVector& Element : Array)
	{
		if(( FMath::IsNearlyEqual(Element.X,  Value.X, 0.0005f) || IgnoreX) &&
			(FMath::IsNearlyEqual(Element.Y,  Value.Y, 0.0005f) || IgnoreY) &&
			(FMath::IsNearlyEqual(Element.Z,  Value.Z, 0.0005f) || IgnoreZ))
		{
			return Index;
		}
		Index++;
	}
	return INDEX_NONE;
}

void UGS_ArrayLibrary::ZeroVectorValue(FVector& Value, bool ZeroX, bool ZeroY, bool ZeroZ)
{
	if(ZeroX) Value.X = 0.0f;
	if(ZeroY) Value.Y = 0.0f;
	if(ZeroZ) Value.Z = 0.0f;
}

void UGS_ArrayLibrary::AppendUniqueVectors(TArray<FVector>& Array, const TArray<FVector>& In)
{
	for(const FVector& Vector : In)
	{
		Array.AddUnique(Vector);
	}
}

TArray<FIntPoint> UGS_ArrayLibrary::GetAllPairVariations(const TArray<int32>& Array)
{
	TArray<FIntPoint> Result;
	for(int32 i = 0; i < Array.Num() ;i++)
	{
		for(int32 j = i + 1; j < Array.Num() ;j++)
		{
			if(!Result.Contains(FIntPoint{Array[j],Array[i]}))
			{
				Result.AddUnique({Array[i],Array[j]});
			}
		}
	}
	return Result;
}

int32 UGS_ArrayLibrary::CountSharedElements(const TArray<FVector>& Array1, const TArray<FVector>& Array2)
{
	int32 Count = 0;
	for(auto Element : Array1)
	{
		if(Array2.Find(Element) != INDEX_NONE)
		{
			Count++;
		}
	}
	return Count;
}

int32 UGS_ArrayLibrary::GetClosestPointInArray(const FVector& Point, const TArray<FVector>& Array)
{
	int32 Index = 0;
	float MinDistance = TNumericLimits< float >::Max();
	for(const FVector& Element : Array)
	{
		const float Distance = FVector::Distance(Point, Element);
		if(Distance < MinDistance)
		{
			Index = Array.Find(Element);
			MinDistance = Distance;
		}
	}
	return Index;
}
