#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "GS_ActionButton.generated.h"

class UGS_ActionInfo;
class UGS_ActionDataAsset;

UCLASS()
class GRANDSTRATEGYGAME_API UGS_ActionButton : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	UGS_ActionInfo* GetAction();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UGS_ActionDataAsset> ActionAsset;
	
};
