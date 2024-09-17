
#include "BaseLibraries/GS_Library.h"

#include "Algo/RemoveIf.h"
#include "BaseData/GS_MapData.h"
#include "Blueprint/UserWidget.h"
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
#if WITH_EDITOR
	Actor->SetActorLabel(NewActorLabel);
#endif
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

AActor* UGS_Library::SpawnActor(UObject* Context, const FTransform Transform, const TSubclassOf<AActor> Class)
{
	return Context->GetWorld()->SpawnActor<AActor>(Class.Get(), Transform);
}

AGS_GameState* UGS_Library::GetGSGameState(UObject* Context)
{
	return Cast<AGS_GameState>(Context->GetWorld()->GetGameState());
}

AGS_Map* UGS_Library::GetMap(UObject* Context)
{
	return GetGSGameState(Context)->MapDataAsset->Map.Get();
}

UDataAsset* UGS_Library::GetDataAsset(UDataAsset* DataAsset, TSubclassOf<UDataAsset> ClassType)
{
	return DataAsset; 
}

FString UGS_Library::AddIndentation(const FString& InputText, int32 NumSpaces)
{
	FString Indentation = FString::ChrN(NumSpaces, TEXT(' '));
	TArray<FString> Lines;
	InputText.ParseIntoArrayLines(Lines);

	for (FString& Line : Lines)
	{
		Line = Indentation + Line;
	}

	return FString::Join(Lines, TEXT("\n"));
}

FString UGS_Library::AddSpacesBeforeCapitals(const FString& Input)
{
	FString Result;
	for (int32 i = 0; i < Input.Len(); i++)
	{
		if (FChar::IsUpper(Input[i]) && i > 0)
		{
			Result.AppendChar(' ');
		}
		Result.AppendChar(Input[i]);
	}
	return Result;
}

float UGS_Library::GetCurveTime(const UCurveFloat* Curve, float Value)
{
	int32 KeysNum = Curve->FloatCurve.GetNumKeys();
	for(int32 i = 0 ; i < KeysNum ; i++)
	{
		FRichCurveKey LastKey = Curve->FloatCurve.Keys[i];
		if(LastKey.Value < Value) 
		{
			if(i == 0)
			{
				return Curve->FloatCurve.Keys[0].Time;
			}
			FRichCurveKey FirstKey = Curve->FloatCurve.Keys[i-1];
			ensure(FirstKey.InterpMode == RCIM_Linear);
			float Alpha = (FirstKey.Value - Value) / (FirstKey.Value - LastKey.Value);
			return FMath::Lerp(FirstKey.Time, LastKey.Time, Alpha);
		}
	}
	return Curve->FloatCurve.Keys.Last().Time;
}

void UGS_Library::RemoveEmptyStrings(TArray<FString>& Array)
{
	Array.RemoveAll([](const FString& String)
	{
		return String.IsEmpty();
	});
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

