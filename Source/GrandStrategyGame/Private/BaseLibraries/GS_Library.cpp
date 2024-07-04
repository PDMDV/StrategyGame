
#include "BaseLibraries/GS_Library.h"

#include "BaseData/GS_MapData.h"
#include "Components/SplineComponent.h"
#include "Game/GS_GameState.h"
#include "Map/GS_Map.h"

FLinearColor UGS_Library::GetRandomColor(const FRandomColorParameters& Parameters)
{
	if(Parameters.CustomSeed)
	{
		FMath::RandInit(Parameters.Seed);
	}
	const float Red = FMath::FRandRange(Parameters.RedMinimum,Parameters.RedMaximum);
	const float Green = FMath::FRandRange(Parameters.GreenMinimum,Parameters.GreenMaximum);
	const float Blue = FMath::FRandRange(Parameters.BlueMinimum,Parameters.BlueMaximum);
	return FLinearColor(Red,Green,Blue);
}

TArray<FVector2D>& UGS_Library::GenerateUV(TArray<FVector2D>& UV, const TArray<FVector>& Vertices, FVector2D Division)
{
	UV.Empty();
	for(const FVector& Vertex : Vertices)
	{
		UV.Push({Vertex.X / Division.X,
						Vertex.Y / Division.Y}); 
	}
	return UV;
}

void UGS_Library::SetActorLabel(AActor* Actor, const FString& NewActorLabel)
{
	Actor->SetActorLabel(NewActorLabel); 
}

void UGS_Library::DestroyComponent(UActorComponent* Component)
{
	Component->DestroyComponent();
}

void UGS_Library::SetSplineTangentLength(USplineComponent* Spline, int TangentIndex, float NewTangentLength)
{
	FVector Tangent = Spline->GetTangentAtSplinePoint(TangentIndex, ESplineCoordinateSpace::World);
	Tangent.Normalize();
	Tangent *= NewTangentLength;
	Spline->SetTangentAtSplinePoint(TangentIndex,Tangent,ESplineCoordinateSpace::World);
}

void UGS_Library::CorrectSpline(USplineComponent* Spline)
{
	using ESplineCoordinateSpace::Local;
	using ESplineCoordinateSpace::World;
	
	for(int Index = 0 ; Index < Spline->GetNumberOfSplinePoints() ; Index++)
	{
		FVector PreviousSplinePointLocation;
		FVector NextSplinePointLocation;
		
		float TangentLength = Spline->GetTangentAtSplinePoint(Index, Local).Length();
		FVector CurrentPointLocation = Spline->GetLocationAtSplinePoint(Index, World);
		
		const bool HasPrevious = Index - 1 >= 0;
		const bool HasNext = Index + 1 <= Spline->GetNumberOfSplinePoints() - 1;
		
		if(HasPrevious)
		{
			PreviousSplinePointLocation = Spline->GetLocationAtSplinePoint(Index - 1, World);
			float DistanceToPreviousPoint = FVector::Distance(PreviousSplinePointLocation, CurrentPointLocation);
			if(TangentLength > DistanceToPreviousPoint)
			{
				SetSplineTangentLength(Spline, Index, DistanceToPreviousPoint);
				TangentLength = DistanceToPreviousPoint;
			}
		}
		if(HasNext)
		{
			NextSplinePointLocation = Spline->GetLocationAtSplinePoint(Index + 1, World);
			float DistanceToNextPoint = FVector::Distance(NextSplinePointLocation, CurrentPointLocation);
			if(TangentLength > DistanceToNextPoint)
			{
				SetSplineTangentLength(Spline, Index, DistanceToNextPoint);
			}
		}
		if(HasPrevious && HasNext)
		{
			const bool PreviousAndNextHaveTheSamePosition = PreviousSplinePointLocation == NextSplinePointLocation;
			if(PreviousAndNextHaveTheSamePosition)
			{
				FVector Distance = (PreviousSplinePointLocation - CurrentPointLocation).GetSafeNormal();
				FVector NewTangent = FVector{Distance.Y, Distance.X, Distance.Z} * 50.f;
				Spline->SetTangentAtSplinePoint(Index,NewTangent,World);
			}
		}
	}
}

AGS_GameState* UGS_Library::GetGSGameState(UObject* Context)
{
	return Cast<AGS_GameState>(Context->GetWorld()->GetGameState());
}

AGS_Map* UGS_Library::GetMap(UObject* Context)
{
	return GetGSGameState(Context)->MapDataAsset->Map.Get();
}

void UGS_Library::DrawDebugLines(UObject* Context, TArray<FVector> Points, FVector Offset, FColor Color, bool bEndLoop)
{
	if(!Context->GetWorld()) return;
	for(int32 Index = 0 ; Index < Points.Num() - 1 ; Index++)
	{
		DrawDebugLine(Context->GetWorld(),Points[Index] + Offset, Points[Index+1] + Offset, Color, false, 10.f, 2.0f, 1.0f);
	}
	if(bEndLoop && Points.Num() >= 3)
	{
		DrawDebugLine(Context->GetWorld(),Points[0] + Offset, Points.Last() + Offset, Color, false, 10.f, 2.0f, 1.0f);
	}
}

