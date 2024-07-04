#pragma once

#include "CoreMinimal.h"
#include "GS_Cost.generated.h"

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_Cost : public UObject
{
	GENERATED_BODY()

	UGS_Cost();

public:

	// Required by BlueprintLibraries
	UWorld* GetWorld() const override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool CanAffordCost(UObject* Source, UObject* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Pay(UObject* Source, UObject* Target);
};
