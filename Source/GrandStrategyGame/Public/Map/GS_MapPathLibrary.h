// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GS_MapLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_MapPathLibrary.generated.h"

struct GS_Graph
{
	GS_Graph(const TArray<FCellInfo>& InCells) : Cells(InCells){};
	
	typedef int32 FNodeRef;
	bool IsValidRef(FNodeRef NodeRef) const { return NodeRef < Cells.Num() && NodeRef > 0; };
	FNodeRef GetNeighbour(const FNodeRef& NodeRef, const int32 NeighbourIndex) const
	{
		return Cells[NodeRef].NeighborsCellsIndexes[NeighbourIndex];
	};
	int32 GetNeighbourCount(FNodeRef NodeRef) const { return Cells[NodeRef].NeighborsCellsIndexes.Num();}

	const TArray<FCellInfo>& Cells;
};

struct GS_PathFilter
{
	GS_PathFilter(const TArray<FCellInfo>& InCells) : Cells(InCells) {}

	FVector::FReal GetHeuristicScale() const
	{
		return 1.;
	}

	FVector::FReal GetHeuristicCost(const int32 StartNodeRef, const int32 EndNodeRef) const
	{
		return GetTraversalCost(StartNodeRef, EndNodeRef);
	}

	FVector::FReal GetTraversalCost(const int32 StartNodeRef, const int32 EndNodeRef) const
	{
		return FVector::Distance( Cells[StartNodeRef].MassCenter, Cells[EndNodeRef].MassCenter);
	}

	bool IsTraversalAllowed(const int32 NodeA, const int32 NodeB) const
	{
		return Cells[NodeB].TerrainType == 1;
	}

	bool WantsPartialSolution() const
	{
		return true;
	}

	const TArray<FCellInfo>& Cells;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_MapPathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure)
	static TArray<int32> GetNextApexPathIndexes(const TArray<FApexPair>& RiverPaths, FApexPair ApexPair);

	UFUNCTION(BlueprintPure)
	static void CalculatePathStrength(const TArray<FApexPair>& RiverPaths, TArray<float>& FirstApexes, TArray<float>& SecondApexes);

	UFUNCTION(BlueprintPure)
	static TArray<int32> FindCellPath( const FCellMap& Map, const int32 Start, const int32 Goal, bool& Success);
	
	UFUNCTION(BlueprintPure, meta=(AutoCreateRefTerm="BlockedApexes"))
	static TArray<FApexPair> GetRiverPath(const FCellMap& Map, const FApexInfo& Start, const TArray<FApexInfo>& BlockedApexes);
};
