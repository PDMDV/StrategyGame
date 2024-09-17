
#pragma once

#include "CoreMinimal.h"
#include "GS_ActionInstance.h"
#include "BaseData/GS_Object.h"
#include "Effect/GS_EffectInfo.h"
#include "GS_ActionInfo.generated.h"

class UGS_ActionInstance;
class URequirement;

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_ActionInfo : public UGS_Object
{
	GENERATED_BODY()

	UGS_ActionInfo();
	
public:   
	
	UFUNCTION(BlueprintCallable)
	UGS_ActionInstance* CreateInstance(UObject* Source, UObject* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UGS_ActionInstance* Perform(UObject* Source, UObject* Target, bool& Success);
	
	UFUNCTION(BlueprintPure)
	bool FulfilsRequirements(UObject* Source, UObject* Target);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Requirements", DisplayPriority = 0))
	TArray<TObjectPtr<URequirement>> Requirements;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Effects", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_EffectInfo>> Effects;
	
	UPROPERTY(BlueprintReadWrite,  meta = (DisplayName = "Action Class", DisplayPriority = 0))
	TSubclassOf<UGS_ActionInstance> InstanceClass = UGS_ActionInstance::StaticClass();
};
