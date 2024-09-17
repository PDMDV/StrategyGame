
#include "BaseLibraries/GS_PointsManipulationLibrary.h"

#include "Algo/ForEach.h"
#include "BaseLibraries/GS_ArrayLibrary.h"
#include "Map/GS_MapLibrary.h"
#include "Voronoi/Voronoi.h"

void UGS_PointsManipulationLibrary::MoreEvenlyDistributePoints(TArray<FVector>& Points, const FBox& BoundsIn, const float Strength)
{
	if(Points.IsEmpty()) return;
	
	FVoronoiDiagram VoronoiDiagram;
	VoronoiDiagram.Initialize(Points, BoundsIn, 1.0f);
	
	TArray<FVoronoiCellInfo> AllCells;
	VoronoiDiagram.ComputeAllCells(AllCells);

	int32 Index = 0;
	for(FVoronoiCellInfo Cell : AllCells)
	{
		Cell.Vertices.RemoveAll([](FVector In){return In.Z < 0;});
		for(FVector& Vertex : Cell.Vertices)
		{
			Vertex.Z = 0;
		}
		FVector Centered = UGS_ArrayLibrary::GetCenterOfPoints(Cell.Vertices);
		Centered = FMath::VInterpTo(Points[Index], Centered, FMath::Clamp(Strength, 0,1), 1.0f);
		Points[Index] = Centered;
		Index++;
	}
	if(Strength > 1.0)
	{
		MoreEvenlyDistributePoints(Points, BoundsIn, Strength - 1.0f);
	}
}

void UGS_PointsManipulationLibrary::MoreEvenlyDistributeCells(TArray<FCellInfo>& CellPoints, const FBox& BoundsIn, const float Strength)
{
	TArray<FVector> Points;
	Points.Reserve(CellPoints.Num());
	for(FCellInfo Cell : CellPoints)
	{
		Points.Add(Cell.VoronoiPoint);
	}
	
	MoreEvenlyDistributePoints(Points, BoundsIn, Strength);

	int Index = 0; 
	for(FVector Point : Points)
	{
		CellPoints[Index++].VoronoiPoint = Point;
	}
}
