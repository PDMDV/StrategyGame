#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_BaseObjectData.h"
#include "Effect/GS_EffectInfo.h"
#include "Requirements/Requirement.h"
#include "GS_MissionData.generated.h"

UCLASS()
class GRANDSTRATEGYGAME_API UGS_MissionData : public UGS_BaseObjectData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Requirements", DisplayPriority = 0))
	TArray<TObjectPtr<URequirement>> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Rewards", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_EffectInfo>> Rewards;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsCapable(UObject* Source, UObject* Target);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool ApplyRewards(UObject* Source, UObject* Target);
};
