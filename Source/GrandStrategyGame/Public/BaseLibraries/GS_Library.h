#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_Library.generated.h"

class AGS_Map;
class AGS_GameState;
class USplineComponent;

USTRUCT(BlueprintType)
struct FRandomColorParameters
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	float RedMaximum = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	float RedMinimum = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float GreenMaximum = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	float GreenMinimum = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float BlueMaximum = 1.0f;
	
	UPROPERTY(BlueprintReadWrite)
	float BlueMinimum = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool CustomSeed = false;

	UPROPERTY(BlueprintReadWrite)
	int32 Seed = 0;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Context"))
	static void DrawDebugLines(UObject* Context, TArray<FVector> Points, FVector Offset = FVector(0,0,0), FColor Color = FColor::Black, bool bEndLoop = false);
	
	UFUNCTION(BlueprintPure, meta = (AutoCreateRefTerm = "Parameters"))
	static FLinearColor GetRandomColor(const FRandomColorParameters& Parameters = FRandomColorParameters());

	UFUNCTION(BlueprintCallable)
	static TArray<FVector2D>&  GenerateUV(UPARAM(ref) TArray<FVector2D>& UV, const TArray<FVector>& Vertices, FVector2D Division);

	UFUNCTION(BlueprintCallable)
	static void SetActorLabel(AActor* Actor, const FString& NewActorLabel);
	
	UFUNCTION(BlueprintCallable)
	static void DestroyComponent(UActorComponent* Component);

	UFUNCTION(BlueprintCallable)
	static void SetSplineTangentLength(USplineComponent* Spline, int TangentIndex, float NewTangentLength);

	UFUNCTION(BlueprintCallable)
	static void CorrectSpline(USplineComponent* Spline);
	
	UFUNCTION(BlueprintCallable)
	static AActor* SpawnActor(UObject* Context, const FTransform Transform, TSubclassOf<AActor> Class);
	
	UFUNCTION(BlueprintPure)
	static AGS_GameState* GetGSGameState(UObject* Context);

	UFUNCTION(BlueprintPure)
	static AGS_Map* GetMap(UObject* Context);

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "ClassType"))
	static UDataAsset* GetDataAsset(UDataAsset* DataAsset, TSubclassOf<UDataAsset> ClassType);

	UFUNCTION(BlueprintPure)
	static FString AddIndentation(const FString& InputText, int32 NumSpaces);
	
	UFUNCTION(BlueprintPure)
    static FString AddSpacesBeforeCapitals(const FString& Input);

	UFUNCTION(BlueprintPure)
	static float GetCurveTime(const UCurveFloat* Curve, float Value);

	UFUNCTION(BlueprintCallable)
	static void RemoveEmptyStrings( UPARAM(ref)TArray<FString>& Array);
};
