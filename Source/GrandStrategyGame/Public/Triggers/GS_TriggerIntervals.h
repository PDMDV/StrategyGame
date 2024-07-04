#pragma once

#include "CoreMinimal.h"
#include "Triggers/GS_Trigger.h"
#include "GS_TriggerIntervals.generated.h"

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_TriggerIntervals : public UGS_Trigger
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite)
	int32 LastInterval;
};
