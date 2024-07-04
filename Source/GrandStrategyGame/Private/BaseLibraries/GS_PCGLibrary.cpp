
#include "BaseLibraries\GS_PCGLibrary.h"

#include "Metadata/PCGMetadataAccessor.h"

TArray<FPCGPoint> UGS_PCGLibrary::GetAllPointsWithAttributeValueInteger32(const TArray<FPCGPoint>& Points, const UPCGMetadata* Metadata, FName AttributeName, int32 Value)
{
	TArray<FPCGPoint> Result;
	for(const FPCGPoint& Point : Points)
	{
		const int32 PointValue = UPCGMetadataAccessorHelpers::GetInteger32Attribute(Point, Metadata, AttributeName);
		if(PointValue == Value)
		{
			Result.Add(Point);
		}
	}

	return Result;
}

void UGS_PCGLibrary::SortPointsByRotation(TArray<FPCGPoint>& Points, ERotatorAxis AxisType)
{
	TFunction<bool(const FPCGPoint&, const FPCGPoint&)> Predicate;
	if(AxisType == Pitch)
	{
		Predicate= [](const FPCGPoint& A, const FPCGPoint&  B) { return A.Transform.Rotator().Pitch < B.Transform.Rotator().Pitch;};
	}
	else if (AxisType == Roll)
	{
		Predicate= [](const FPCGPoint& A, const FPCGPoint& B) { return A.Transform.Rotator().Roll < B.Transform.Rotator().Roll;};
	}
	else if (AxisType == Yaw)
	{
		Predicate= [](const FPCGPoint& A, const FPCGPoint& B) { return A.Transform.Rotator().Yaw < B.Transform.Rotator().Yaw;};
	}
	
	Algo::Sort(Points, Predicate);
}
