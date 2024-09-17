#pragma once

#include "CoreMinimal.h"
#include "Effect/GS_EffectInfo.h"
#include "GS_Cost.generated.h"

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_Cost : public UGS_EffectInfo
{
	GENERATED_BODY()

	UGS_Cost();
	
	virtual bool IsCapable_Implementation(UObject* Source, UObject* Target, UObject* Outer) override;
};
