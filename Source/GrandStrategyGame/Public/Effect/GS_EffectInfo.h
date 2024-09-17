#pragma once

#include "CoreMinimal.h"
#include "GS_EffectInstance.h"
#include "BaseData/GS_Object.h"
#include "GS_EffectInfo.generated.h"

class UGameplayEffect;

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_EffectInfo : public UGS_Object
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	UGS_EffectInstance* Apply(UObject* Source, UObject* Target, UObject* Outer, bool& Success);
	
	UFUNCTION(BlueprintCallable)
	UGS_EffectInstance* CreateEffect(UObject* Source, UObject* Target, UObject* Outer);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsCapable(UObject* Source, UObject* Target, UObject* Outer);
	virtual bool IsCapable_Implementation(UObject* Source, UObject* Target, UObject* Outer);

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Effect Class", DisplayPriority = 0))
	TSubclassOf<UGS_EffectInstance> InstanceClass;
};
