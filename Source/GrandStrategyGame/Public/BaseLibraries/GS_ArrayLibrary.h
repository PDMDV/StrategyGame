#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_ArrayLibrary.generated.h"

UCLASS()
class GRANDSTRATEGYGAME_API UGS_ArrayLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure)
	static TArray<FVector> ConvertToVector(TArray<FVector2D> Points);

	UFUNCTION(BlueprintPure)
	static FVector GetCenterOfPoints(const TArray<FVector>& Points);

	UFUNCTION(BlueprintPure)
	static TArray<FVector2D> ConvertToVector2D(TArray<FVector> Points);

	UFUNCTION(BlueprintCallable)
	static void AddToAll(UPARAM(ref)  TArray<FVector>& Array, FVector Value);

	UFUNCTION(BlueprintCallable)
	static void FillArrayInt32(UPARAM(ref) TArray<int32>& Array, int32 Value, int32 Size) {Array.Init(Value, Size);}

	UFUNCTION(BlueprintCallable)
	static void FillArrayVector(UPARAM(ref) TArray<FVector>& Array, FVector Value, int32 Size) {Array.Init(Value, Size);}

	UFUNCTION(BlueprintCallable)
	static void FillArrayVector2D(UPARAM(ref) TArray<FVector2D>& Array, FVector2D Value, int32 Size) {Array.Init(Value, Size);}

	UFUNCTION(BlueprintCallable)
	static void FillArrayLinearColor(UPARAM(ref) TArray<FLinearColor>& Array, FLinearColor Value, int32 Size) {Array.Init(Value, Size);}

	UFUNCTION(BlueprintCallable)
	static void ZeroVectorValue(UPARAM(ref) FVector& Value, bool ZeroX = false, bool ZeroY = false, bool ZeroZ = false);

	UFUNCTION(BlueprintCallable)
	static void AppendUniqueVectors(UPARAM(ref) TArray<FVector>& Array, const TArray<FVector>& In);
	
	UFUNCTION(BlueprintPure)
	static int32 FindVectorIgnoringAxis(const TArray<FVector>& Array, FVector Value, bool IgnoreX = false, bool IgnoreY = false, bool IgnoreZ = false);
	
	UFUNCTION(BlueprintPure)
	static int32 CountSharedElements(const TArray<FVector>& Array1, const TArray<FVector>& Array2);

	UFUNCTION(BlueprintPure)
	static TArray<FIntPoint> GetAllPairVariations(const TArray<int32>& Array);

	UFUNCTION(BlueprintPure)
	static int32 GetClosestPointInArray(const FVector& Point, const TArray<FVector>& Array);

	UFUNCTION(BlueprintPure)
	static TArray<int32> FindSmallestElements(TArray<float> Array, int32 Number);

	UFUNCTION(BlueprintPure)
	static float Accumulate(const TArray<float>& Array);
};
