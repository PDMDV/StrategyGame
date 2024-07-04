#pragma once

#include "CoreMinimal.h"
#include "PCGPoint.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_PCGLibrary.generated.h"

UENUM(BlueprintType)
enum ERotatorAxis
{
	Pitch UMETA(DisplayName = "Pitch"),
	Yaw UMETA(DisplayName = "Yaw"),
	Roll UMETA(DisplayName = "Roll"),
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_PCGLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	static TArray<FPCGPoint> GetAllPointsWithAttributeValueInteger32(const TArray<FPCGPoint>& Points, const UPCGMetadata* Metadata, FName AttributeName, int32 Value);
	
	UFUNCTION(BlueprintCallable)
	static void SortPointsByRotation(UPARAM(ref) TArray<FPCGPoint>& Points, ERotatorAxis AxisType);
};
