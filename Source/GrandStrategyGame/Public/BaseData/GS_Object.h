#pragma once

#include "CoreMinimal.h"
#include "GS_Object.generated.h"

UCLASS(Blueprintable)
class GRANDSTRATEGYGAME_API UGS_Object : public UObject
{
	GENERATED_BODY()

public:
	
	// Required by BlueprintLibraries
	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	FString GetToolTipMessage(UObject* Source, UObject* Target);
};
