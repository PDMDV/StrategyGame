
#include "Map/GS_MapPathLibrary.h"

#include "GraphAStar.h"
#include "Map/GS_MapLibrary.h"

TArray<int32> UGS_MapPathLibrary::GetNextApexPathIndexes(const TArray<FApexPair>& RiverPaths, FApexPair ApexPair)
{
	TArray<int32> Result;
	while(true)
	{
		const FApexPair* NextPair = Algo::FindByPredicate(RiverPaths, [&](const FApexPair& Pair)
		{
			return Pair.Second.MyIndex == ApexPair.First.MyIndex;
		});
		if(NextPair == nullptr) break;
		Result.Add(RiverPaths.Find(*NextPair));
		ApexPair = *NextPair;
	}
	return Result;
}

void UGS_MapPathLibrary::CalculatePathStrength(const TArray<FApexPair>& RiverPaths, TArray<float>& FirstApexes, TArray<float>& SecondApexes)
{
	FirstApexes.SetNum(RiverPaths.Num());
	SecondApexes.SetNum(RiverPaths.Num());
	
	int32 Index = 0;
	for(const FApexPair& RiverPath : RiverPaths)
	{
		const float Strength = FVector::Distance(RiverPath.First.Position, RiverPath.Second.Position);
		FirstApexes[Index] += Strength;
		for(const int32 NextPathIndex : GetNextApexPathIndexes(RiverPaths, RiverPath))
		{
			FirstApexes[NextPathIndex] += Strength;
			SecondApexes[NextPathIndex] += Strength;
		}
		Index++;
	}
}

TArray<int32> UGS_MapPathLibrary::FindCellPath(const FCellMap& Map, const int32 Start, const int32 Goal, bool& Success)
{
	FGraphAStar<GS_Graph> Graph(Map.Cells);
	TArray<int32> Path;
	EGraphAStarResult Result = Graph.FindPath(Start, Goal, GS_PathFilter(Map.Cells), Path);
	Success = (Result == SearchSuccess);
	return Path;
}

TArray<FApexPair> UGS_MapPathLibrary::GetRiverPath(const FCellMap& Map, const FApexInfo& Start, const TArray<FApexInfo>& BlockedApexes)
{
	auto GetRelevantNextApexes = [&](const FApexInfo& InApex)
	{
		TArray<FApexInfo> Result;
		for(const FApexInfo& Apex : UGS_MapLibrary::GetAllApexNeighbourApexes(Map, InApex))
		{
			if(!UGS_MapLibrary::HasApexTerrainTypeNeighbour(Map,Apex,0) && InApex.Position.Z <= Apex.Position.Z)
			{
				Result.Add(Apex);
			}
		}
		return Result;
	};

	TArray<FApexPair> PathResult;
	TArray<FApexInfo> FrontApexes;
	TArray<FApexInfo> NewFrontApexes;
	TArray<FApexInfo> UsedApexes;
	FrontApexes.Add(Start);
	UsedApexes.AddUnique(Start);
	while(FrontApexes.Num() > 0)
	{
		for(auto FrontApex : FrontApexes)
		{
			for(const FApexInfo& Apex : GetRelevantNextApexes(FrontApex))
			{
				if( PathResult.Find(FApexPair(FrontApex,Apex)) == INDEX_NONE && !UsedApexes.Contains(Apex) && !BlockedApexes.Contains(Apex))
				{
					PathResult.Add(FApexPair(FrontApex,Apex));
					NewFrontApexes.Add(Apex);
					UsedApexes.AddUnique(Apex);
				}
			}
		}
		FrontApexes = NewFrontApexes;
		NewFrontApexes.Empty();
	}
	return PathResult;
}
