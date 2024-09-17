#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Voronoi/Voronoi.h"
#include "GS_MapLibrary.generated.h"

struct FVoronoiCellInfo;

struct FVoronoiCellInfoWithCenter
{
	FVoronoiCellInfo VoronoiCell;
	FVector Center;
};

USTRUCT(BlueprintType)
struct FBorderLoop
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Loop;
};

USTRUCT(BlueprintType)
struct FCellOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TesselationLevel = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFlat = false; // like the Earth

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HighMultiplier = 1.0;
};

USTRUCT(BlueprintType)
struct FCellConnectionOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BorderMaxRecursionDepth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BorderDeviationRatio = 0.3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinimumSegmentLength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFlat = false; // like the Earth

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HighMultiplier = 1.0;
};

USTRUCT(BlueprintType)
struct FCellInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector MassCenter = {};

	UPROPERTY(BlueprintReadWrite)
	FVector VoronoiPoint = {};
	
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> ApexesIndexes;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> NeighborsCellsIndexes;

	UPROPERTY(BlueprintReadWrite)
	int32 TerrainType = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 MyIndex = -1;

	UPROPERTY(BlueprintReadWrite)
	int32 SubgraphIndex = 0;
};

USTRUCT(BlueprintType)
struct FApexInfo
{
	GENERATED_BODY()

	FApexInfo(){};
	FApexInfo(const FVector& InPosition) : Position(InPosition){};

	friend bool operator==(const FApexInfo& Lhs, const FApexInfo& RHS)
	{
		return Lhs.MyIndex == RHS.MyIndex;
	}

	friend bool operator!=(const FApexInfo& Lhs, const FApexInfo& RHS)
	{
		return !(Lhs == RHS);
	}
	
	UPROPERTY(BlueprintReadWrite)
	FVector Position;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> NeighborApexes;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> NeighborCells;

	UPROPERTY(BlueprintReadWrite)
	int32 MyIndex = -1;
};

USTRUCT(BlueprintType)
struct FApexPair
{
	GENERATED_BODY()
	friend bool operator==(const FApexPair& Lhs, const FApexPair& RHS)
	{
		return (Lhs.First == RHS.First && Lhs.Second == RHS.Second) || (Lhs.First == RHS.Second && Lhs.Second == RHS.First);
	}

	friend bool operator!=(const FApexPair& Lhs, const FApexPair& RHS)
	{
		return !(Lhs == RHS);
	}

	FApexPair(){};

	FApexPair(FApexInfo InFirst, FApexInfo InSecond) : First(InFirst), Second(InSecond){}
	
	UPROPERTY(BlueprintReadWrite)
	FApexInfo First;

	UPROPERTY(BlueprintReadWrite)
	FApexInfo Second;
};

USTRUCT(BlueprintType)
struct FCellPair
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FCellInfo First;

	UPROPERTY(BlueprintReadWrite)
	FCellInfo Second;
};

USTRUCT(BlueprintType)
struct FEdgeInfo
{
	GENERATED_BODY()
	friend bool operator==(const FEdgeInfo& Lhs, const FEdgeInfo& RHS)
	{
		return (Lhs.FirstApex == RHS.FirstApex && Lhs.SecondApex == RHS.SecondApex) || (Lhs.FirstApex == RHS.SecondApex && Lhs.SecondApex == RHS.FirstApex);
	}

	friend bool operator!=(const FEdgeInfo& Lhs, const FEdgeInfo& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(BlueprintReadWrite)
	FApexInfo FirstApex;

	UPROPERTY(BlueprintReadWrite)
	FCellInfo FirstCell;

	UPROPERTY(BlueprintReadWrite)
	FApexInfo SecondApex;
	
	UPROPERTY(BlueprintReadWrite)
	FCellInfo SecondCell;
};

USTRUCT(BlueprintType)
struct FCellMap
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FCellInfo> Cells;

	UPROPERTY(BlueprintReadWrite)
	TArray<FApexInfo> Apexes;
};

UENUM(BlueprintType)
enum class ECentralPointType : uint8
{
	MassCenter = 0 UMETA(DisplayName = "Mass Center"),
	VoronoiPoint= 1 UMETA(DisplayName = "Voronoi Center"),
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_MapLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static TArray<FVoronoiCellInfo> BuildVoronoiCells(TArray<FVector> Points, const FBox& BoundsIn);
	static TArray<FVoronoiCellInfo> BuildVoronoiCellsWithSubgraphs(TArray<FVector> Points, const FBox& BoundsIn, int32 MinSubgraphSize, int32 MaxSubgraphSize, TArray<int32>& SubgraphsFragmentsSizes, TArray<FVector>& AllCenters);
	static void CalculateApexes(FCellMap& CellMap, FCellInfo& Cell, FVoronoiCellInfo VoronoiCell);
	static FCellMap ConvertVoronoiCellsToCellMap(const TArray<FVector>& Points, const TArray<FVoronoiCellInfo>& AllCells);
	static void CalculateApexesNeighbours(FCellMap& CellMap);
	static void ApplyPreviousMap(FCellMap& Results, const FCellMap& Previous);

public:
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Previous"))
	static FCellMap BuildCellMap(TArray<FVector> Points, const FBox& BoundsIn, const FCellMap& Previous);
	
	UFUNCTION(BlueprintCallable)
	static FCellMap BuildCellMapWithSubgraphs(TArray<FVector> Points, const FBox& BoundsIn, int32 MinSubgraphSize, int32 MaxSubgraphSize);

	UFUNCTION(BlueprintCallable)
	static void FindEdgesLoop(const TArray<FEdgeInfo>& Edges, TArray<FEdgeInfo>& Result, TArray<FEdgeInfo>& Remains);

	UFUNCTION(BlueprintPure)
	static TArray<FVector> GetCellApexesPositions(UPARAM(ref) const FCellMap& Map, int32 CellIndex);

	UFUNCTION(BlueprintPure)
	static TArray<FApexPair> GetAllApexesPairs(UPARAM(ref) const FCellMap& Map);

	UFUNCTION(BlueprintPure)
	static TArray<FEdgeInfo> GetAllEdges(UPARAM(ref) const FCellMap& Map);

	UFUNCTION(BlueprintPure)
	static TArray<FApexPair> GetAllCellApexPair(UPARAM(ref) const FCellMap& Map, int32 CellIndex);

	UFUNCTION(BlueprintPure)
	static FEdgeInfo GetCommonEdge(const FCellMap& Map, FCellInfo FirstCell, FCellInfo SecondCell);
	
	UFUNCTION(BlueprintPure)
	static TArray<FEdgeInfo> GetAllCellEdges(UPARAM(ref) const FCellMap& Map, FCellInfo CellInfo);

	UFUNCTION(BlueprintPure)
	static TArray<int32> GetBorderApexIndexes(const FCellMap& Map, const TArray<int32>& CellIndexes);

	UFUNCTION(BlueprintPure)
	static bool IsNext(const FCellMap& Map,const TArray<int32>& CellIndexes, int32 CurrentApex, int32 NextApex);
	
	UFUNCTION(BlueprintPure)
	static int32 GetNextApex(const FCellMap& Map, const TArray<int32>& BorderApexes, const TArray<int32>& CellIndexes, int32 PreviousApex, int32 CurrentApex);

	UFUNCTION(BlueprintPure)
	static FBorderLoop ExtractBorderLoop(const FCellMap& Map, UPARAM(ref) TArray<int32>& BorderApexes, const TArray<int32>& CellIndexes);

	UFUNCTION(BlueprintPure)
	static TArray<FBorderLoop> GetAllCellBorders(UPARAM(ref) const FCellMap& Map, const TArray<int32>& CellIndexes);

	UFUNCTION(BlueprintPure)
	static TArray<FVector> GetApexesPositions(UPARAM(ref) const FCellMap& Map, const TArray<int32>& ApexIndexes);

	UFUNCTION(BlueprintPure)
	static TArray<FEdgeInfo> GetEdges(UPARAM(ref) const FCellMap& Map, const TArray<int32>& ApexIndexes);

	UFUNCTION(BlueprintPure)
	static FEdgeInfo GetEdge(UPARAM(ref) const FCellMap& Map, const FApexPair& ApexPair);

	UFUNCTION(BlueprintPure)
	static bool CorrectOrder(FEdgeInfo& EdgeInfo);

	UFUNCTION(BlueprintPure)
	static void GetEdgeRegionVertices(FEdgeInfo Edge, FVector& A, FVector& B, FVector& C, FVector& D, bool& SwappedApexes, ECentralPointType CentralPointType = ECentralPointType::VoronoiPoint);

	UFUNCTION(BlueprintPure)
	static bool HasTerrainTypeNeighbour(UPARAM(ref) const FCellMap& Map, int32 TerrainType, int32 CellIndex);

	UFUNCTION(BlueprintPure)
	static bool HasApexTerrainTypeNeighbour(const FCellMap& Map, const FApexInfo& ApexInfo, int32 TerrainType);
	
	UFUNCTION(BlueprintPure)
	static TArray<FApexInfo> GetAllApexNeighbourApexes(const FCellMap& Map, const FApexInfo& ApexInfo);

	UFUNCTION(BlueprintPure)
	static FCellConnectionOptions GetCellConnectionOptions(UPARAM(ref) const TMap<FIntPoint, FCellConnectionOptions>& Map, FIntPoint Pair, bool& Success);
};
