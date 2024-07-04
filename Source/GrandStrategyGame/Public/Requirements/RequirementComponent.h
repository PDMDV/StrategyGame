
#pragma once

#include "CoreMinimal.h"
#include "RequirementComponent.generated.h"

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class URequirementComponent : public UObject
{
	GENERATED_BODY()

public:

	URequirementComponent();

	// Required by BlueprintLibraries
	UWorld* GetWorld() const override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsCompliant(UObject* Source, UObject* Target);
};
