
#pragma once

#include "CoreMinimal.h"
#include "GS_BaseObjectData.h"
#include "Engine/DataAsset.h"
#include "GS_SituationData.generated.h"

class UGS_Trigger;
class URequirementComponent;
class UGS_Effect;
class URequirementsList;
class UGS_Action;

USTRUCT(BlueprintType)
struct FReaction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Reaction", DisplayPriority = 0))
	TObjectPtr<UGS_Action> Reaction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ActionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ActionDescription;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_SituationData : public UGS_BaseObjectData
{
	GENERATED_BODY()

	UGS_SituationData();
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool CanOccur(UObject* Source, UObject* Target);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Occurrence Requirements", DisplayPriority = 0))
	TArray<TObjectPtr<URequirementComponent>> OccurrenceRequirements;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Start Actions", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_Action>> StartActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Start Effects", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_Effect>> StartEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, SimpleDisplay, meta = (DisplayName = "Reactions", DisplayPriority = 0))
	TArray<FReaction> Reactions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Triggers", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_Trigger>> Triggers;
};
