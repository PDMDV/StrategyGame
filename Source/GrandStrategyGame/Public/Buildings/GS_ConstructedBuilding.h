#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_Object.h"
#include "GS_ConstructedBuilding.generated.h"

class UGS_BuildingData;

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_ConstructedBuilding : public UGS_Object
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn=true))
	TObjectPtr<UGS_BuildingData> BuildingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn=true))
	int32 Mark = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn=true))
	int32 LevelToUpgrade = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn=true))
	int32 LevelToBuild = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn=true))
	float Progress = 0.0f;

	UFUNCTION(BlueprintPure)
	int32 GetTotalLevel() const { return LevelToUpgrade + LevelToBuild; }
};
