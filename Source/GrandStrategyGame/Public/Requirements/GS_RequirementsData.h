#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GS_RequirementsData.generated.h"

class URequirement;

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_RequirementsData : public UDataAsset
{
	GENERATED_BODY()

	UGS_RequirementsData();
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Requirements", DisplayPriority = 0))
	TArray<TObjectPtr<URequirement>> Requirements;

	UFUNCTION(BlueprintPure)
	virtual bool IsCompliant(UObject* Source, UObject* Target);
	
};
