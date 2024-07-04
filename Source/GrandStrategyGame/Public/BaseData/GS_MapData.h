
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GS_MapData.generated.h"

class AGS_Map;

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_MapData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<AGS_Map> Map;
	
};
