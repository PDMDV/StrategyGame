
#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_Object.h"
#include "Requirement.generated.h"

class UGS_IntegersDataSlot;

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories, DefaultToInstanced)
class URequirement : public UGS_Object
{
	GENERATED_BODY()

public:

	URequirement();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsCompliant(UObject* Source, UObject* Target);
};

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories, DefaultToInstanced)
class URequirement_WithIntParam : public URequirement
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Data Slot", DisplayPriority = 0))
	TObjectPtr<UGS_IntegersDataSlot> Param;
};