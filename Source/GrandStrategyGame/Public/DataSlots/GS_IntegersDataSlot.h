#pragma once

#include "CoreMinimal.h"
#include "DataSlots/GS_DataSlot.h"
#include "GS_IntegersDataSlot.generated.h"


USTRUCT(BlueprintType, Blueprintable)
struct FIntegersDataSlot
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Data Type", DisplayPriority = 0))
	TObjectPtr<UGS_IntegersDataSlot> Data;
};

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories, DefaultToInstanced)
class GRANDSTRATEGYGAME_API UGS_IntegersDataSlot : public UGS_DataSlot
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	TArray<int32> GetData(UObject* Source, UObject* Target);
};

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories, DefaultToInstanced)
class GRANDSTRATEGYGAME_API UGS_IntegersDataSlot_WithParam : public UGS_IntegersDataSlot
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Data Type", DisplayPriority = 0))
	TObjectPtr<UGS_IntegersDataSlot> Param;
};
