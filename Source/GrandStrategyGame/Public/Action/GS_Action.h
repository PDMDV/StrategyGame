
#pragma once

#include "CoreMinimal.h"
#include "GS_Action.generated.h"

class UGS_Cost;
class URequirementComponent;

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_Action : public UObject
{
	GENERATED_BODY()

	UGS_Action();
	
public:   
	
	// Required by BlueprintLibraries
	UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsCapable(UObject* Source, UObject* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Perform(UObject* Source, UObject* Target);
	
	UFUNCTION(BlueprintPure)
	bool FulfilsRequirements(UObject* Source, UObject* Target);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Occurrence Requirements", DisplayPriority = 0))
	TArray<TObjectPtr<URequirementComponent>> Requirements;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Costs", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_Cost>> Costs;
};
