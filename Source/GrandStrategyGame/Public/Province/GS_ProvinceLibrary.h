#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Province/GS_ResourceLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_ProvinceLibrary.generated.h"

class AGS_Settlement;
class UGS_ResourceData;

USTRUCT(BlueprintType)
struct FProvince
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AGS_Settlement* Settlement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 MyIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 TerrainType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector Center;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Region;
	
	UPROPERTY(VisibleAnywhere , BlueprintReadWrite)
	TArray<FResource> Resources;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite)
	FGameplayTagContainer Tags;
};
UCLASS()
class GRANDSTRATEGYGAME_API UGS_ProvinceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void AddTag(UPARAM(ref) FProvince& Province, const FGameplayTag& TagToAdd);

	UFUNCTION(BlueprintCallable)
	static bool RemoveTag(UPARAM(ref) FProvince& Province, const FGameplayTag& TagToRemove);
	
};
