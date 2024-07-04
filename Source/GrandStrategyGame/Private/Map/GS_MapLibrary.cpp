
#include "Map\GS_MapLibrary.h"

#include "BaseLibraries/GS_ArrayLibrary.h"
#include "BaseLibraries/GS_MathLibrary.h"
#include "Voronoi/Voronoi.h"

FCellMap UGS_MapLibrary::BuildVoronoi(TArray<FVector> Points, const FBox& BoundsIn, const FCellMap& Previous)
{
	if(Points.IsEmpty()) return {};
	FVoronoiDiagram VoronoiDiagram;
	VoronoiDiagram.Initialize(Points, BoundsIn, 1.0f);

	TArray<FVoronoiCellInfo> AllCells;
	VoronoiDiagram.ComputeAllCells(AllCells);

	FCellMap Results;
	int32 CellIndex = 0;
	for(FVoronoiCellInfo Cell : AllCells)
	{
		Cell.Neighbors.RemoveAll([](int32 In){return In < 0;});
		Cell.Vertices.RemoveAll([](FVector In){return In.Z < 0;});
		Cell.Vertices = UGS_MathLibrary::ConvexHullAlgorithm(Cell.Vertices);
		FCellInfo ResultCell;
		ResultCell.MassCenter = UGS_ArrayLibrary::GetCenterOfPoints(Cell.Vertices);
		ResultCell.VoronoiPoint = Points[CellIndex];
		ResultCell.MyIndex = CellIndex;
		ResultCell.NeighborsCellsIndexes = Cell.Neighbors;
		for(FVector ApexPosition : Cell.Vertices)
		{
			if(ApexPosition.Z == 1 )
			{
				FApexInfo* Apex = Algo::FindByPredicate(Results.Apexes, [&](const FApexInfo& Apex)
				{
					return ApexPosition.Equals(Apex.Position, 1.0f);
				});
				if(Apex == nullptr)
				{
					int ApexIndex = Results.Apexes.Add(ApexPosition);
					Apex = &Results.Apexes[ApexIndex];
					Apex->MyIndex = ApexIndex;
				}
				ResultCell.ApexesIndexes.Push(Apex->MyIndex);
				Apex->NeighborCells.AddUnique(CellIndex);
			}
		}
		Results.Cells.Add(ResultCell);
		CellIndex++;
	}

	for(FApexInfo& ApexInfo : Results.Apexes)
	{
		for(int32 IndexCell : ApexInfo.NeighborCells)
		{
			int32 CellApexNum = Results.Cells[IndexCell].ApexesIndexes.Num();
			int32 ApexIndexInCell = Results.Cells[IndexCell].ApexesIndexes.Find(ApexInfo.MyIndex);
			
			int32 ApexPreviousIndexInCell = (ApexIndexInCell > 0) ? (ApexIndexInCell-1) % CellApexNum : CellApexNum - 1;
			int32 ApexNextIndexInCell = (ApexIndexInCell+1) % CellApexNum;

			ApexInfo.NeighborApexes.AddUnique(Results.Cells[IndexCell].ApexesIndexes[ApexPreviousIndexInCell]);
			ApexInfo.NeighborApexes.AddUnique(Results.Cells[IndexCell].ApexesIndexes[ApexNextIndexInCell]);
		}
	}
	if(!Previous.Cells.IsEmpty() && Previous.Cells.Num() <= Results.Cells.Num())
	{
		int32 Index = 0;
		for(const FCellInfo& PreviousCell : Previous.Cells)
		{
			Results.Cells[Index].TerrainType = PreviousCell.TerrainType;
			Index++;
		}
	}
	return Results;
}

void UGS_MapLibrary::FindEdgesLoop(const TArray<FEdgeInfo>& Edges, TArray<FEdgeInfo>& Result, TArray<FEdgeInfo>& Remains)
{
	Remains = Edges;
	auto AreConnected = [](const FEdgeInfo& EdgeA, const FEdgeInfo& EdgeB)
	{
		if( EdgeA == EdgeB ) return false;
		return	EdgeA.FirstApex  == EdgeB.FirstApex  ||
				EdgeA.FirstApex  == EdgeB.SecondApex ||
				EdgeA.SecondApex == EdgeB.FirstApex  ||
				EdgeA.SecondApex == EdgeB.SecondApex;
	};

	FEdgeInfo Start = Edges[0];
	FEdgeInfo CurrentEdge = Start;
	bool Success = true;
	const FEdgeInfo* CurrentEdgePtr;
	do
	{
		Result.Add(CurrentEdge);
		Remains.Remove(CurrentEdge);
		CurrentEdgePtr = Algo::FindByPredicate(Edges, [&](const FEdgeInfo& Edge)
		{
			return AreConnected(CurrentEdge, Edge) && !Result.Contains(Edge);
		});
		if(CurrentEdgePtr == nullptr) break;
		CurrentEdge = *CurrentEdgePtr;
		if(Result.Last().SecondApex != CurrentEdge.FirstApex)
		{
			if(Result.Last().FirstApex == CurrentEdge.FirstApex || Result.Last().FirstApex == CurrentEdge.SecondApex)
			{
				Swap(Result.Last().FirstApex, Result.Last().SecondApex);
			}
			if(CurrentEdge.SecondApex == Result.Last().FirstApex || CurrentEdge.SecondApex == Result.Last().SecondApex)
			{
				Swap(CurrentEdge.FirstApex, CurrentEdge.SecondApex);
			}
		}

	}while(CurrentEdge != Start);
	 
	if(!AreConnected(Result[0], Result.Last()))
	{
		Remains = Edges;
		Result.Empty();
	}
}

TArray<FVector> UGS_MapLibrary::GetCellApexesPositions(const FCellMap& Map, int32 CellIndex)
{
	FCellInfo Cell = Map.Cells[CellIndex];
	TArray<FVector> Result;
	for(int32 ApexIndex : Cell.ApexesIndexes)
	{
		Result.Push(Map.Apexes[ApexIndex].Position);
	}
	return Result;
}

 TArray<FApexPair> UGS_MapLibrary::GetAllApexesPairs(const FCellMap& Map)
 {
 	TArray<FApexPair> Result;
 	for(const FApexInfo& ProcessedApex : Map.Apexes)
 	{
 		for(const int32 NeighborApexIndex : ProcessedApex.NeighborApexes)
 		{
		    const FApexInfo& NeighbourApex = Map.Apexes[NeighborApexIndex];
 			if(ProcessedApex.MyIndex < NeighbourApex.MyIndex)
 			{
 				Result.Add({ProcessedApex, NeighbourApex});
 			}  
 		}
 	}
 	return Result;
 }

 TArray<FEdgeInfo> UGS_MapLibrary::GetAllEdges(const FCellMap& Map)
 {
 	TArray<FEdgeInfo> Result;
 	for(FApexPair ApexPair : GetAllApexesPairs(Map))
 	{
 		Result.Push(GetEdge(Map, ApexPair));
 	}
 	return Result;
 }

 TArray<FApexPair> UGS_MapLibrary::GetAllCellApexPair(const FCellMap& Map, int32 CellIndex)
 {
 	if(!Map.Cells.IsValidIndex(CellIndex) || Map.Cells[CellIndex].ApexesIndexes.Num() == 0) return {};
 	
 	TArray<FApexPair> Result;

    const TArray<int32>& ApexesIndexes = Map.Cells[CellIndex].ApexesIndexes;
    const int32 ApexesNum = ApexesIndexes.Num();
 	for(int32 i = 0 ; i <= ApexesNum - 2 ; i++)
 	{
 		Result.Push({Map.Apexes[ApexesIndexes[i]],Map.Apexes[ApexesIndexes[i+1]] });
 	}
	Result.Push({Map.Apexes[ApexesIndexes.Last()], Map.Apexes[ApexesIndexes[0]]});
 	return Result;
 }

FEdgeInfo UGS_MapLibrary::GetCommonEdge(const FCellMap& Map, FCellInfo FirstCell, FCellInfo SecondCell)
{
	TArray<FEdgeInfo> FirstCellEdges = GetAllCellEdges(Map, FirstCell);
	TArray<FEdgeInfo> SecondCellEdges = GetAllCellEdges(Map, SecondCell);

	for(FEdgeInfo Edge : FirstCellEdges)
	{
		if(SecondCellEdges.Contains(Edge))
		{
			return Edge;
		}
	}
	return FEdgeInfo();
}

TArray<FEdgeInfo> UGS_MapLibrary::GetAllCellEdges(const FCellMap& Map, FCellInfo CellInfo)
 {
	if(!Map.Cells.IsValidIndex(CellInfo.MyIndex)) return {};
		
 	TArray<FEdgeInfo> Result;
    TArray<FApexPair> CellApexPairs = GetAllCellApexPair(Map, CellInfo.MyIndex);
 	for(FApexPair ApexPair : CellApexPairs)
 	{
 		Result.Push(GetEdge(Map, ApexPair));
 	}
 	return Result;
 }

TArray<int32> UGS_MapLibrary::GetBorderApexIndexes(const FCellMap& Map, const TArray<int32>& CellIndexes)
{
	TMap<int32, int32> ApexRepetitions;
	for(int32 CellIndex : CellIndexes)
	{
		for( int32 ApexIndex : Map.Cells[CellIndex].ApexesIndexes)
		{
			if(ApexRepetitions.Contains(ApexIndex))
			{
				ApexRepetitions[ApexIndex] += 1;
			}
			else
			{
				ApexRepetitions.Add(ApexIndex, 1);
			}
		}
	}

	TArray<int32> BorderApexes;
	for(auto[ApexIndex, Repetitions]  : ApexRepetitions)
	{
		if(Repetitions <= 2)
		{
			BorderApexes.Add(ApexIndex);
		}
	}
	return BorderApexes;
}

bool UGS_MapLibrary::IsNext(const FCellMap& Map,const TArray<int32>& CellIndexes, int32 CurrentApex, int32 NextApex)
{
	FApexPair ApexPair = {Map.Apexes[CurrentApex],Map.Apexes[NextApex]};
	FEdgeInfo Edge = GetEdge(Map, ApexPair);

	return CellIndexes.Contains(Edge.FirstCell.MyIndex) ^ CellIndexes.Contains(Edge.SecondCell.MyIndex);
}

int32 UGS_MapLibrary::GetNextApex(const FCellMap& Map, const TArray<int32>& BorderApexes, const TArray<int32>& CellIndexes, int32 PreviousApex, int32 CurrentApex)
{
	const FApexInfo& Apex = Map.Apexes[CurrentApex];

	for( int32 NeighbourApex :Apex.NeighborApexes )
	{
		if(NeighbourApex != PreviousApex && BorderApexes.Contains(NeighbourApex) && IsNext(Map, CellIndexes, CurrentApex, NeighbourApex))
		{
			return NeighbourApex;
		}
	}
	return -1;
}

FBorderLoop UGS_MapLibrary::ExtractBorderLoop(const FCellMap& Map, TArray<int32>& BorderApexes, const TArray<int32>& CellIndexes)
{
	FBorderLoop Result;
	int32 StartApex = BorderApexes[0];
	int32 CurrentApexIndex = StartApex;
	int32 PreviousApex = StartApex;
	do
	{
		// TODO Sometimes the apex can't be found. This should be fixed.
		int32 NextApex = GetNextApex(Map, BorderApexes, CellIndexes, PreviousApex, CurrentApexIndex);
		if(NextApex == -1)
		{
			BorderApexes.Empty();
			return {};
		}
		Result.Loop.Add(NextApex);
		PreviousApex = CurrentApexIndex;
		CurrentApexIndex = NextApex;
		BorderApexes.Remove(NextApex);

	}
	while(StartApex != CurrentApexIndex);

	return Result;
}
  
TArray<FBorderLoop> UGS_MapLibrary::GetAllCellBorders(const FCellMap& Map, const TArray<int32>& CellIndexes)
{
	TArray<int32> BorderApexes = GetBorderApexIndexes(Map, CellIndexes);
	TArray<int32> Test = BorderApexes;
	TArray<FBorderLoop> Result;
	while(!BorderApexes.IsEmpty())
	{
		FBorderLoop BorderLoop = ExtractBorderLoop(Map, BorderApexes, CellIndexes);
		if(!BorderLoop.Loop.IsEmpty())
		{
			Result.Add(BorderLoop);
		}
	}
	return Result;
}

TArray<FVector> UGS_MapLibrary::GetApexesPositions(const FCellMap& Map, const TArray<int32>& ApexIndexes)
{
	TArray<FVector> Result;
	for(int32 ApexIndex : ApexIndexes)
	{
		Result.Add(Map.Apexes[ApexIndex].Position);
	}
	return Result;
}

TArray<FEdgeInfo> UGS_MapLibrary::GetEdges(const FCellMap& Map, const TArray<int32>& ApexIndexes)
{
	if(ApexIndexes.Num() < 2) return {};
	TArray<FEdgeInfo> Result;

	FApexPair ApexPair;
	for(int32 Index = 0 ; Index < ApexIndexes.Num() - 1 ; Index++)
	{
		ApexPair = {Map.Apexes[ApexIndexes[Index]], Map.Apexes[ApexIndexes[Index + 1]]};
		Result.Add(GetEdge(Map, ApexPair));
	}
	ApexPair = {Map.Apexes[ApexIndexes.Last()], Map.Apexes[ApexIndexes[0]]};
	Result.Add(GetEdge(Map, ApexPair));

	return Result;
}

FEdgeInfo UGS_MapLibrary::GetEdge(const FCellMap& Map, const FApexPair& ApexPair)
{
	const TArray<int32> FirstApexNeighbors = Map.Apexes[ApexPair.First.MyIndex].NeighborCells;
	const TArray<int32> SecondApexNeighbors = Map.Apexes[ApexPair.Second.MyIndex].NeighborCells;

	TArray<TArray<int32>::ElementType> CellIndexes = FirstApexNeighbors.FilterByPredicate([&](const int32 Element){return SecondApexNeighbors.Contains(Element);});

	const FCellInfo FirstCell = CellIndexes.Num() >= 1 ? Map.Cells[CellIndexes[0]] : FCellInfo();
	const FCellInfo SecondCell = CellIndexes.Num() >= 2 ? Map.Cells[CellIndexes[1]] : FCellInfo();

	return {ApexPair.First,FirstCell,ApexPair.Second,SecondCell};
}

bool UGS_MapLibrary::CorrectOrder(FEdgeInfo& EdgeInfo)
 {
	bool SwappedApexes = false;
 	if(EdgeInfo.FirstApex.MyIndex > EdgeInfo.SecondApex.MyIndex)
 	{
 		Swap(EdgeInfo.FirstApex,EdgeInfo.SecondApex);
 		SwappedApexes = true;
 	}
 	if(EdgeInfo.FirstCell.MyIndex > EdgeInfo.SecondCell.MyIndex)
 	{
 		Swap(EdgeInfo.FirstCell,EdgeInfo.SecondCell);
 	}
	return SwappedApexes;
 }

void UGS_MapLibrary::GetEdgeRegionVertices(FEdgeInfo Edge, FVector& A, FVector& B, FVector& C, FVector& D, bool& SwappedApexes, ECentralPointType CentralPointType)
 {
 	SwappedApexes = CorrectOrder(Edge);

	A = Edge.FirstApex.Position;
	C = Edge.SecondApex.Position;
 
	if(CentralPointType == ECentralPointType::MassCenter)
	{
		B = Edge.FirstCell.MassCenter;
		D = Edge.SecondCell.MassCenter;
	}
	else if(CentralPointType == ECentralPointType::VoronoiPoint)
	{
		B = Edge.FirstCell.VoronoiPoint;
		D = Edge.SecondCell.VoronoiPoint;
	}
	if(Edge.FirstCell.MyIndex == -1)
	{
		B = Edge.FirstApex.Position;
	}
	if(Edge.SecondCell.MyIndex == -1)
	{
		D = Edge.SecondApex.Position;
	}
 }

bool UGS_MapLibrary::HasTerrainTypeNeighbour(const FCellMap& Map, int32 TerrainType, int32 CellIndex)
{
	FCellInfo CellInfo = Map.Cells[CellIndex];
	for(int32 NeighbourIndex : CellInfo.NeighborsCellsIndexes)
	{
		if(Map.Cells[NeighbourIndex].TerrainType == TerrainType)
		{
			return true;
		}
	}
	return false;
}

bool UGS_MapLibrary::HasApexTerrainTypeNeighbour(const FCellMap& Map, const FApexInfo& ApexInfo, int32 TerrainType)
{
	for(const int32 NeighbourCellIndex : ApexInfo.NeighborCells)
	{
		if(Map.Cells[NeighbourCellIndex].TerrainType == TerrainType)
		{
			return true;
		}
	}
	return false;
}

TArray<FApexInfo> UGS_MapLibrary::GetAllApexNeighbourApexes(const FCellMap& Map, const FApexInfo& ApexInfo)
{
	TArray<FApexInfo> Result;
	for(const auto ApexIndex : ApexInfo.NeighborApexes)
	{
		Result.Add(Map.Apexes[ApexIndex]);
	}
	return Result;
}

FCellConnectionOptions UGS_MapLibrary::GetCellConnectionOptions(const TMap<FIntPoint, FCellConnectionOptions>& Map, FIntPoint Pair, bool& Success)
{
	Success = false;
	for(const FIntPoint PairVariant : {FIntPoint{Pair.X,Pair.Y},FIntPoint{Pair.Y,Pair.X}})
	{
		const FCellConnectionOptions* Result = Map.Find(PairVariant);
		if(Result)
		{
			Success = true;
			return *Result;
		}
	}
	return {};
}
