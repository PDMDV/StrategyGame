#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_GeometryScriptLibrary.generated.h"

USTRUCT(BlueprintType)
struct FArea
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector A = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector B = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector C = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector D = {};
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_GeometryScriptLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	static TArray<int> GetMeshBorderIndexes( UDynamicMesh* TargetMesh, bool UsePolyGroup = false, int32 TriangleGroup = 1);
	
	
	UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, DisplayName = "Get Boundary Vertices"))
	static UPARAM(DisplayName = "Vertices") TArray<FVector> GetBoundaryVertices( UDynamicMesh* TargetMesh, bool UsePolyGroup = false, int32 TriangleGroup = 1);

	UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, DisplayName = "Get Boundary Vertices In Area"))
	static UPARAM(DisplayName = "Target Mesh") TArray<FVector> GetBoundaryVerticesInArea( UDynamicMesh* TargetMesh, FArea Area, bool UsePolyGroup = false, int32 TriangleGroup = 1);

	UFUNCTION(BlueprintPure, Category = "GeometryScript|MeshQueries", meta = (ScriptMethod, DisplayName = "Get Triangle At Position"))
	static UPARAM(DisplayName = "Target Mesh") int32 GetTriangleAtPosition( UDynamicMesh* TargetMesh, FVector Position, bool& Success);

	UFUNCTION(BlueprintCallable, Category = "GeometryScript|MeshEdit", meta = (ScriptMethod, DisplayName = "Append Closed Line"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* AppendClosedLine( UDynamicMesh* TargetMesh, TArray<FVector> LinePoints, float LineWidth, float Offset);
	
	UFUNCTION(BlueprintCallable, Category = "GeometryScript|Subdivide", meta = (ScriptMethod, DisplayName = "Tessellate"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* Tessellate( UDynamicMesh* TargetMesh, float TriangleMaxArea, int32 TessellationLevel);

	UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta = (ScriptMethod, DisplayName = "Apply Height Map To Mesh"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* ApplyHeightTexture( UDynamicMesh* TargetMesh, UTexture2D* Texture, float Multiplier = 1.0f, float Center = 0.5f);
	
	UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta = (DisplayName = "Apply Height Map To Points"))
	static void ApplyHeightTextureToPoints(UPARAM(ref) TArray<FVector>& Points, UTexture2D* Texture, FIntPoint MapSize, float Multiplier = 1.0f, float Center = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta = (ScriptMethod, DisplayName = "Set Edge Height"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetEdgeHeight( UDynamicMesh* TargetMesh, FVector Start, FVector End, FVector FirstCellCenter,FVector SecondCellCenter, float Height);

	UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Set Last Added PolyGroup Index"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SetLastAddedPolyGroupIndex( UDynamicMesh* TargetMesh, int32 NewPolyGroupIndex);

	UFUNCTION(BlueprintCallable, Category = "GeometryScript|PolyGroups", meta = (ScriptMethod, DisplayName = "Get PolyGroupsFroTriangleIDs"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* GetPolyGroupsFromTriangleIDs( UDynamicMesh* TargetMesh, const FGeometryScriptIndexList& TriangleIDs, FGeometryScriptIndexList& OutPolyGroupIDs);

	UFUNCTION(BlueprintCallable, Category = "GeometryScript|Deformations", meta = (ScriptMethod, DisplayName = "Snap To Component"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* SnapToComponent( UDynamicMesh* TargetMesh, UPrimitiveComponent* Component, FVector Offset = FVector(0,0,0));

	UFUNCTION(BlueprintCallable, Category = "GeometryScript|UV", meta = (ScriptMethod, DisplayName = "Calculate Line UV"))
	static UPARAM(DisplayName = "Target Mesh") UDynamicMesh* CalculateLineUV( UDynamicMesh* TargetMesh);
	
	UFUNCTION(BlueprintCallable, Category = "GeometryScript|Buffers", meta = (ScriptMethod, DisplayName = "Append Buffers"))
	static void AppendBuffers( UPARAM(ref) FGeometryScriptSimpleMeshBuffers& Buffer, const FGeometryScriptSimpleMeshBuffers& Source);
};
