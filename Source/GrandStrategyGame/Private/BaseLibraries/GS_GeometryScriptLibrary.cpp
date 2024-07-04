// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLibraries/GS_GeometryScriptLibrary.h"

#include "BaseLibraries\GS_ArrayLibrary.h"
#include "BaseLibraries\GS_MathLibrary.h"
#include "MeshBoundaryLoops.h"
#include "MeshUtilitiesCommon.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "UDynamicMesh.h"
#include "AssetUtils/Texture2DUtil.h"
#include "Components/DynamicMeshComponent.h"
#include "DynamicMesh/MeshAttributeUtil.h"
#include "GeometryScript/GeometryScriptTypes.h"
#include "GeometryScript/MeshBasicEditFunctions.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"
#include "Image/ImageBuilder.h"
#include "Polygroups/PolygroupSet.h"

TArray<int> UGS_GeometryScriptLibrary::GetMeshBorderIndexes(UDynamicMesh* TargetMesh, bool UsePolyGroup, int32 TriangleGroup)
{
	if (TargetMesh == nullptr)
	{
		return {};
	}
	TArray<int> Result;
	TargetMesh->ProcessMesh([&](const FDynamicMesh3& ReadMesh)
	{
		FDynamicMesh3::FEdge FirstEdge;
		
		if(UsePolyGroup)
		{
			TUniquePtr<UE::Geometry::FPolygroupSet> PolyGroupSet = MakeUnique<UE::Geometry::FPolygroupSet>(&ReadMesh, UE::Geometry::FPolygroupLayer());
			bool Success = false;
			for(int EdgeIndex : ReadMesh.BoundaryEdgeIndicesItr())
			{
				FDynamicMesh3::FEdge ProcessedEdge = ReadMesh.GetEdge(EdgeIndex);
				if (PolyGroupSet->GetGroup(ProcessedEdge.Tri.A) == TriangleGroup || PolyGroupSet->GetGroup(ProcessedEdge.Tri.B) == TriangleGroup)
				{
					Success = true;
					FirstEdge = ProcessedEdge;
					break;
				}
			}
			if(!Success)
			{
				return;
			}
		}
		else
		{
			FirstEdge = ReadMesh.GetEdge(*ReadMesh.BoundaryEdgeIndicesItr().begin());
		}
		
		if(FirstEdge.Vert.A < 0 || FirstEdge.Vert.B < 0)
		{
			return;
		}
		Result.Push(FirstEdge.Vert.A);
		Result.Push(FirstEdge.Vert.B);
		
		FDynamicMesh3::FEdge Edge;
		int32 LastResultSize;
		do
		{
			LastResultSize = Result.Num();
			TArray<int> EdgeArray;
			int VertID = Result.Last();
			ReadMesh.GetAllVtxBoundaryEdges(VertID, EdgeArray); 
			for(int EdgeID : EdgeArray)
			{
				Edge = ReadMesh.GetEdge(EdgeID); 
				Result.AddUnique(Edge.Vert.A);
				Result.AddUnique(Edge.Vert.B);
			}
			
		} while(Result.Num() != LastResultSize);
	});
	
	return Result;
}

TArray<FVector> UGS_GeometryScriptLibrary::GetBoundaryVertices(UDynamicMesh* TargetMesh, bool UsePolyGroup, int32 TriangleGroup)
{
	if (TargetMesh == nullptr)
	{
		return {};
	}
	
	TArray<int> BorderVertexIndexes = GetMeshBorderIndexes(TargetMesh, UsePolyGroup, TriangleGroup);
	
	TArray<FVector> Result;
	TargetMesh->ProcessMesh([&](const FDynamicMesh3& ReadMesh)
	{
		for(int VertexIndex : BorderVertexIndexes)
		{
			Result.Push(ReadMesh.GetVertex(VertexIndex));
		}
	});
	return Result;
}

TArray<FVector> UGS_GeometryScriptLibrary::GetBoundaryVerticesInArea(UDynamicMesh* TargetMesh, FArea Area, bool UsePolyGroup, int32 TriangleGroup)
{
	if (TargetMesh == nullptr)
	{
		return {};
	}
	
	TArray<FVector> BoundaryVertices = GetBoundaryVertices(TargetMesh, UsePolyGroup, TriangleGroup);
	TArray<FVector> Result;
	for(FVector Vertex : BoundaryVertices)
	{
		if(UGS_MathLibrary::PointInTriangle(Area.A, Area.B, Area.C, Vertex) || UGS_MathLibrary::PointInTriangle(Area.A, Area.C, Area.D, Vertex))
		{
			Result.Add(Vertex);
		}
	}
	int32 FirstIndex = UGS_ArrayLibrary::GetClosestPointInArray(Area.A, Result);
	int32 LastIndex = UGS_ArrayLibrary::GetClosestPointInArray(Area.C, Result);
	
	if((LastIndex - 1 == FirstIndex) || (LastIndex == 0))
	{
		Algo::Reverse(Result);
	}
	FirstIndex = UGS_ArrayLibrary::GetClosestPointInArray(Area.A, Result);
	Algo::Rotate(Result, FirstIndex);
	
	return Result;
}

int32 UGS_GeometryScriptLibrary::GetTriangleAtPosition(UDynamicMesh* TargetMesh, FVector Position, bool& Success)
{
	if (TargetMesh == nullptr)
	{
		return 0;
	}
	int32 Result = -1;
	TargetMesh->ProcessMesh([&](const FDynamicMesh3& ReadMesh)
	{
		for (int32 TriangleIndex : ReadMesh.TriangleIndicesItr())
		{
			const FIntVector Triangle = ReadMesh.GetTriangle(TriangleIndex);
			const FVector A = ReadMesh.GetVertex(Triangle.X);
			const FVector B = ReadMesh.GetVertex(Triangle.Y);
			const FVector C = ReadMesh.GetVertex(Triangle.Z);
			if(UGS_MathLibrary::PointInTriangle(A, B, C, Position))
			{
				Result = TriangleIndex;
				break;
			}
		}
	});
	Success = (Result != -1) ? true : false;
	return Result;
}

UDynamicMesh* UGS_GeometryScriptLibrary::AppendClosedLine(UDynamicMesh* TargetMesh, TArray<FVector> LinePoints, float LineWidth, float Offset)
{
	if (TargetMesh == nullptr || LinePoints.IsEmpty())
	{
		return TargetMesh;
	}	

	TArray<FVector2D> OutsideVertices = UGS_MathLibrary::PolygonsOffset(UGS_ArrayLibrary::ConvertToVector2D(LinePoints), LineWidth/2 + Offset);
	OutsideVertices.Add(FVector2D(OutsideVertices[0]));
	
	TArray<FVector2D> InsideVertices = UGS_MathLibrary::PolygonsOffset(UGS_ArrayLibrary::ConvertToVector2D(LinePoints), -LineWidth/2 + Offset);
	Algo::Reverse(InsideVertices);
	InsideVertices.Add(FVector2D(InsideVertices[0]));

	TArray<FVector2D> PolygonVertices;
	PolygonVertices.Append(OutsideVertices);
	PolygonVertices.Append(InsideVertices);

	FVector ConnectionA = FVector{OutsideVertices[0],0};
	FVector ConnectionB = FVector{InsideVertices[0],0};

	UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendTriangulatedPolygon(TargetMesh, FGeometryScriptPrimitiveOptions(), FTransform(), PolygonVertices);
	
	TargetMesh->EditMesh([&](FDynamicMesh3& EditMesh)
	{
		TArray<int32> EdgeToMerge;
		for(int32 EdgeIndex : EditMesh.EdgeIndicesItr())
		{
			FDynamicMesh3::FEdge Edge = EditMesh.GetEdge(EdgeIndex);
			FVector3d VertexA = EditMesh.GetVertex(Edge.Vert.A);
			FVector3d VertexB = EditMesh.GetVertex(Edge.Vert.B);

			if((VertexA == ConnectionA || VertexA == ConnectionB) && (VertexB == ConnectionA || VertexB == ConnectionB))
			{
				EdgeToMerge.Add(EdgeIndex);
			}
			
		}
		if(EdgeToMerge.Num() == 2)
		{
			DynamicMeshInfo::FMergeEdgesInfo MergeInfo{};
			EditMesh.MergeEdges(EdgeToMerge[0], EdgeToMerge[1],MergeInfo);
		}
		
	}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown);
	return TargetMesh;
}

UDynamicMesh* UGS_GeometryScriptLibrary::Tessellate(UDynamicMesh* TargetMesh, float TriangleMaxArea, int32 TessellationLevel)
{
	if (TargetMesh == nullptr)
	{
		return TargetMesh;
	}
	
	if(TessellationLevel == 0) return TargetMesh;
	
	TargetMesh->EditMesh([&](FDynamicMesh3& Mesh)
	{
		auto CalculateTriangleArea = [&](const FIntVector Triangle)
		{
			const FVector3f A = FVector3f(Mesh.GetVertex(Triangle.X));
			const FVector3f B = FVector3f(Mesh.GetVertex(Triangle.Y));
			const FVector3f C = FVector3f(Mesh.GetVertex(Triangle.Z));
			return TriangleUtilities::ComputeTriangleArea(A,B,C);
		};
		
		TArray<int32> TrianglesToProcess;
		for (int32 Index : Mesh.TriangleIndicesItr())
		{
			FIntVector Triangle = Mesh.GetTriangle(Index);
			if(CalculateTriangleArea(Triangle) > TriangleMaxArea)
			{
				TrianglesToProcess.Add(Index);
			}
		}
		TUniquePtr<UE::Geometry::FPolygroupSet> PolyGroupSet = MakeUnique<UE::Geometry::FPolygroupSet>(&Mesh, UE::Geometry::FPolygroupLayer());
		for(int32 TriangleIndex : TrianglesToProcess)
		{
			const FIntVector Triangle = Mesh.GetTriangle(TriangleIndex);
			const FVector A = Mesh.GetVertex(Triangle.X);
			const FVector B = Mesh.GetVertex(Triangle.Y);
			const FVector C = Mesh.GetVertex(Triangle.Z);
			
			int AB = Mesh.AppendVertex(FMath::Lerp(A,B,0.5));
			int BC = Mesh.AppendVertex(FMath::Lerp(B,C,0.5));
			int CA = Mesh.AppendVertex(FMath::Lerp(C,A,0.5));
			
			Mesh.SetTriangle(TriangleIndex, FIntVector(AB,BC,CA));
			int TriIndex1 = Mesh.AppendTriangle(FIntVector(Triangle.X,AB,CA));
			int TriIndex2 = Mesh.AppendTriangle(FIntVector(Triangle.Y,BC,AB));
			int TriIndex3 = Mesh.AppendTriangle(FIntVector(Triangle.Z,CA,BC));
			
			int32 GroupID = PolyGroupSet->GetTriangleGroup(TriangleIndex);
			PolyGroupSet->SetGroup(TriIndex1, GroupID, Mesh);
			PolyGroupSet->SetGroup(TriIndex2, GroupID, Mesh);
			PolyGroupSet->SetGroup(TriIndex3, GroupID, Mesh);
		}
	});
	return TargetMesh;
}

UDynamicMesh* UGS_GeometryScriptLibrary::ApplyHeightTexture(UDynamicMesh* TargetMesh, UTexture2D* Texture,float Multiplier, float Center)
{
	if (TargetMesh == nullptr)
	{
		return TargetMesh;
	}
	if(Texture == nullptr)
	{
		return TargetMesh;
	}
	
	UE::Geometry::TImageBuilder<FVector4f> ImageData;

	if (!UE::AssetUtils::ReadTexture(Texture, ImageData))
	{
		return TargetMesh;
	}
	int64 TextureWidth = ImageData.GetDimensions().GetWidth();
	int64 TextureHeight = ImageData.GetDimensions().GetHeight();
	TargetMesh->EditMesh([&](FDynamicMesh3& EditMesh)
	{
		for (const int32 VertexID : EditMesh.VertexIndicesItr())
		{
			FVector3d VertexPosition = EditMesh.GetVertex(VertexID);
			int32 U = FMath::Clamp((int)VertexPosition.X,0,TextureWidth-1);
			int32 V = FMath::Clamp((int)VertexPosition.Y,0,TextureHeight-1);
	
			const FVector4f Pixel = ImageData.GetPixel(U,V);
			VertexPosition.Z = FMath::Clamp(Pixel.X - Center,0,1.f) * Multiplier;
			EditMesh.SetVertex(VertexID, VertexPosition);
		}
	}, EDynamicMeshChangeType::MeshVertexChange, EDynamicMeshAttributeChangeFlags::VertexPositions);
	return TargetMesh;
}

void UGS_GeometryScriptLibrary::ApplyHeightTextureToPoints(TArray<FVector>& Points, UTexture2D* Texture,  FIntPoint MapSize, float Multiplier, float Center)
{
	UE::Geometry::TImageBuilder<FVector4f> ImageData;
	if (!UE::AssetUtils::ReadTexture(Texture, ImageData))
	{
		return;
	}
	const int64 TextureWidth = ImageData.GetDimensions().GetWidth();
	const int64 TextureHeight = ImageData.GetDimensions().GetHeight();
	for(FVector& Point : Points)
	{
		int32 X = (float)Point.X / (static_cast<float>(MapSize.X) / Texture->GetSizeX());
		int32 Y = (float)Point.Y / (static_cast<float>(MapSize.Y) / Texture->GetSizeY());
		int32 U = FMath::Clamp(X,0,TextureWidth-1);
		int32 V = FMath::Clamp(Y,0,TextureHeight-1);
		
		const FVector4f Pixel = ImageData.GetPixel(U,V);
		Point.Z = FMath::Clamp(Pixel.X - Center,0,1.f) * Multiplier;
	}
}

UDynamicMesh* UGS_GeometryScriptLibrary::SetEdgeHeight(UDynamicMesh* TargetMesh, FVector Start, FVector End, FVector FirstCellCenter, FVector SecondCellCenter, float Height)
{
	if (TargetMesh == nullptr)
	{
		return TargetMesh;
	}
	
	TargetMesh->EditMesh([&](FDynamicMesh3& EditMesh)
	{
		TArray<int> BorderVertexIndexes = GetMeshBorderIndexes(TargetMesh);

		int StartVertexID = -1;
		int EndVertexID = -1;

		FVector3d Vertex;
		int32 ArrayIndex = 0;
		for(int VertexID : BorderVertexIndexes)
		{
			Vertex = EditMesh.GetVertex(VertexID);
			if( Vertex.X == Start.X && Vertex.Y == Start.Y)
			{
				StartVertexID = ArrayIndex;
			}
			if( Vertex.X == End.X && Vertex.Y == End.Y)
			{
				EndVertexID = ArrayIndex;
			}
			ArrayIndex++;
		}
		
		if(StartVertexID == -1 || EndVertexID == -1)
		{
			return;
		}
		if(EndVertexID < StartVertexID)
		{
			Swap(StartVertexID,EndVertexID);
		}
		FVector3d MidVertex = EditMesh.GetVertex(BorderVertexIndexes[(EndVertexID + StartVertexID) / 2]);
		Start.Z = 0.0f;
		End.Z = 0.0f;
		FirstCellCenter.Z = 0.0f;
		SecondCellCenter.Z = 0.0f;
		
		if(	!UGS_MathLibrary::PointInTriangle(Start, End, FirstCellCenter, MidVertex) &&
			!UGS_MathLibrary::PointInTriangle(Start, End, SecondCellCenter, MidVertex))
		{
			Swap(StartVertexID,EndVertexID);
		}
		
		for(ArrayIndex = StartVertexID; ArrayIndex != EndVertexID + 1; ArrayIndex++)
		{
			if(ArrayIndex == BorderVertexIndexes.Num())
			{
				ArrayIndex = 0;
			}
			FVector3d VertexPosition = EditMesh.GetVertex(BorderVertexIndexes[ArrayIndex]);
			VertexPosition.Z = Height;
			EditMesh.SetVertex(BorderVertexIndexes[ArrayIndex], VertexPosition);
		}
		
	}, EDynamicMeshChangeType::MeshVertexChange, EDynamicMeshAttributeChangeFlags::VertexPositions);
	return TargetMesh;
}

UDynamicMesh* UGS_GeometryScriptLibrary::SetLastAddedPolyGroupIndex(UDynamicMesh* TargetMesh, int32 NewPolyGroupIndex)
{
	if (TargetMesh == nullptr)
	{
		return TargetMesh;
	}
	
	TargetMesh->EditMesh([&](FDynamicMesh3& Mesh)
	{
		const int32 LastPolyGroupID = Mesh.MaxGroupID() - 1;

		int TriangleID = 0;
		for(const int PolyGroupID : *Mesh.GetTriangleGroupsBuffer())
		{
			if(PolyGroupID == LastPolyGroupID)
			{
				Mesh.SetTriangleGroup(TriangleID ,NewPolyGroupIndex);
			}
			TriangleID++;
		}
		
	}, EDynamicMeshChangeType::AttributeEdit, EDynamicMeshAttributeChangeFlags::TriangleGroups);

	return TargetMesh;
}

UDynamicMesh* UGS_GeometryScriptLibrary::GetPolyGroupsFromTriangleIDs(UDynamicMesh* TargetMesh, const FGeometryScriptIndexList& TriangleIDs, FGeometryScriptIndexList& OutPolyGroupIDs)
{
	if (TargetMesh == nullptr)
	{
		return TargetMesh;
	}
	
	TargetMesh->ProcessMesh([&](const FDynamicMesh3& ReadMesh)
	{
		TUniquePtr<UE::Geometry::FPolygroupSet> PolyGroupSet = MakeUnique<UE::Geometry::FPolygroupSet>(&ReadMesh, UE::Geometry::FPolygroupLayer());
		OutPolyGroupIDs.Reset(EGeometryScriptIndexType::Triangle);
		for(int32 TriangleIndex : *TriangleIDs.List)
		{
			OutPolyGroupIDs.List->Add(PolyGroupSet->GetTriangleGroup(TriangleIndex));
		}
	});
	return TargetMesh;
}

UDynamicMesh* UGS_GeometryScriptLibrary::SnapToComponent(UDynamicMesh* TargetMesh, UPrimitiveComponent* Component, FVector Offset)
{
	if (TargetMesh == nullptr || Component == nullptr)
	{
		return TargetMesh;
	}
	FVector ComponentLocation = Component->GetComponentLocation();
	
	TargetMesh->EditMesh([&](FDynamicMesh3& EditMesh)
	{
		for (const int32 VertexID : EditMesh.VertexIndicesItr())
		{
			FVector3d VertexPosition = EditMesh.GetVertex(VertexID);
			FVector CombinedOffset = ComponentLocation + Offset;
			FVector Start = VertexPosition + FVector3d{0, 0, 10000} + CombinedOffset;
			FVector End = VertexPosition + FVector3d{0, 0, -10000} + CombinedOffset;
			FHitResult Result;
			FCollisionQueryParams Params;
			Params.bTraceComplex = true;
			Component->LineTraceComponent(Result, Start, End, Params);
			
			if(Result.ImpactPoint.Length())
			{
				EditMesh.SetVertex(VertexID, Result.ImpactPoint - ComponentLocation - CombinedOffset);
			}
		}
	}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::VertexPositions);
	return TargetMesh;
}

UDynamicMesh* UGS_GeometryScriptLibrary::CalculateLineUV(UDynamicMesh* TargetMesh)
{
	if (TargetMesh == nullptr)
	{
		return TargetMesh;
	}

	auto Vertices = GetMeshBorderIndexes(TargetMesh);
	TargetMesh->EditMesh([&](FDynamicMesh3& EditMesh)
	{
		const UE::Geometry::FMeshBoundaryLoops BoundaryLoops(&EditMesh, true);
		if( BoundaryLoops.GetLoopCount() != 2) return;
		
		UE::Geometry::FDynamicMeshUVOverlay* UVOverlay = EditMesh.Attributes()->GetUVLayer(0);

		EditMesh.EnableAttributes();
		EditMesh.EnableVertexUVs({0,0});
		
		float Length0 = 0;
		float Length1 = 0;
		for(const int EdgeIndex : BoundaryLoops.Loops[0].Edges)
		{
			FDynamicMesh3::FEdge Edge = EditMesh.GetEdge(EdgeIndex);
			Length0 += FVector3d::Distance(EditMesh.GetVertex(Edge.Vert.A), EditMesh.GetVertex(Edge.Vert.B));
		}

		for(const int EdgeIndex : BoundaryLoops.Loops[1].Edges)
		{
			FDynamicMesh3::FEdge Edge = EditMesh.GetEdge(EdgeIndex);
			Length1 += FVector3d::Distance(EditMesh.GetVertex(Edge.Vert.A), EditMesh.GetVertex(Edge.Vert.B));
		}

		const bool LongestLoop = (bool)BoundaryLoops.GetLongestLoopIndex();
		UE::Geometry::FEdgeLoop InsideLoop = BoundaryLoops.Loops[(int)!LongestLoop];
		UE::Geometry::FEdgeLoop OutsideLoop = BoundaryLoops.Loops[(int)LongestLoop];
		TArray<int> Inside  = InsideLoop.Vertices;
		TArray<int> Outside = OutsideLoop.Vertices;

		TArray<FVector> Vertices;
		InsideLoop.GetVertices(Vertices);
		int32 ClosestInsideVertexIndex = UGS_ArrayLibrary::GetClosestPointInArray(OutsideLoop.GetVertex(0), Vertices);
		Algo::Rotate(Inside, ClosestInsideVertexIndex);
		
		float InsideLength =  (Length0 < Length1) ? Length0 : Length1;
		float OutsideLength =  (Length0 >= Length1) ? Length0 : Length1;

		float Distance = 0;
		EditMesh.SetVertexUV(Inside[0], {0, 0});
		for(int i = 1 ; i < Inside.Num() ; i++)
		{
			Distance += FVector3d::Distance(EditMesh.GetVertex(Inside[i - 1]), EditMesh.GetVertex(Inside[i]));
			EditMesh.SetVertexUV(Inside[i], {Distance/InsideLength, 0});
		}

		Distance = OutsideLength;
		EditMesh.SetVertexUV(Outside[0], {OutsideLength, 1});
		for(int i = 1 ; i < Outside.Num() ; i++)
		{
			Distance -= FVector3d::Distance(EditMesh.GetVertex(Outside[i - 1]), EditMesh.GetVertex(Outside[i]));
			EditMesh.SetVertexUV(Outside[i], {Distance/OutsideLength, 1});
		}
		
		CopyVertexUVsToOverlay(EditMesh, *EditMesh.Attributes()->PrimaryUV());
		/*for(int TriangleIndex : EditMesh.TriangleIndicesItr())
		{
			UE::Geometry::FIndex3i Triangle = EditMesh.GetTriangle(TriangleIndex);
			int UV0 = UVOverlay->AppendElement(EditMesh.GetVertexUV(Triangle.A));
			int UV1 = UVOverlay->AppendElement(EditMesh.GetVertexUV(Triangle.B));
			int UV2 = UVOverlay->AppendElement(EditMesh.GetVertexUV(Triangle.C));
			UVOverlay->SetTriangle(TriangleIndex, UE::Geometry::FIndex3i(UV0, UV1, UV2), true);
		}*/
	}, EDynamicMeshChangeType::GeneralEdit, EDynamicMeshAttributeChangeFlags::Unknown);
	return TargetMesh;
}

void UGS_GeometryScriptLibrary::AppendBuffers(FGeometryScriptSimpleMeshBuffers& Buffer, const FGeometryScriptSimpleMeshBuffers& Source)
{
	int32 VerticesNum = Buffer.Vertices.Num();
	Buffer.Vertices.Append(Source.Vertices);
	Buffer.Normals.Append(Source.Normals);
	
	Buffer.UV0.Append(Source.UV0);
	Buffer.UV1.Append(Source.UV1);
	Buffer.UV2.Append(Source.UV2);
	Buffer.UV3.Append(Source.UV3);
	Buffer.UV4.Append(Source.UV4);
	Buffer.UV5.Append(Source.UV5);
	Buffer.UV6.Append(Source.UV6);
	Buffer.UV7.Append(Source.UV7);
	
	Buffer.VertexColors.Append(Source.VertexColors);
	for(FIntVector Triangle : Source.Triangles)
	{
		Buffer.Triangles.Add(FIntVector{Triangle.X + VerticesNum,Triangle.Y + VerticesNum,Triangle.Z + VerticesNum});
	}
	Buffer.TriGroupIDs.Append(Source.TriGroupIDs);
}
