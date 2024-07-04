#pragma once

#include "CoreMinimal.h"
#include "RequirementsList.h"
#include "Engine/DataAsset.h"
#include "GS_RequirementsData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_RequirementsData : public UDataAsset
{
	GENERATED_BODY()

	UGS_RequirementsData();
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Requirements", DisplayPriority = 0))
	TObjectPtr<URequirementsList> RequirementsList;

	UFUNCTION(BlueprintPure)
	virtual bool IsCompliant(UObject* Source, UObject* Target);
	
};
