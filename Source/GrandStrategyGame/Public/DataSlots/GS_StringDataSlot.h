
#pragma once

#include "CoreMinimal.h"
#include "DataSlots/GS_DataSlot.h"
#include "GS_StringDataSlot.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FStringDataSlot
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Data Type", DisplayPriority = 0))
	TObjectPtr<UGS_StringDataSlot> Data;
};

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories, DefaultToInstanced)
class GRANDSTRATEGYGAME_API UGS_StringDataSlot : public UGS_DataSlot
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FString GetData(UObject* Source, UObject* Target);
};
