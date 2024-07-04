
#pragma once

#include "CoreMinimal.h"
#include "RequirementsList.generated.h"

class URequirementComponent;

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class GRANDSTRATEGYGAME_API URequirementsList : public UObject
{
	GENERATED_BODY()

public:
	URequirementsList();
	 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "List", DisplayPriority = 0))
	TArray<TObjectPtr<URequirementComponent>> RequirementsList;

	UFUNCTION(BlueprintPure)
	virtual bool IsCompliant(UObject* Source, UObject* Target);
};
 