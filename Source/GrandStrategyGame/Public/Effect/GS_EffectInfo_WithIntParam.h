#pragma once

#include "CoreMinimal.h"
#include "Effect/GS_EffectInfo.h"
#include "GS_EffectInfo_WithIntParam.generated.h"

class UGS_IntegersDataSlot;
UCLASS()
class GRANDSTRATEGYGAME_API UGS_EffectInfo_WithIntParam : public UGS_EffectInfo
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Data Slot", DisplayPriority = 0))
	TObjectPtr<UGS_IntegersDataSlot> Param;
};
