// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BaseData/GS_BaseObjectData.h"
#include "BaseData/GS_ProductionMethod.h"
#include "Requirements/RequirementsList.h"
#include "GS_BuildingData.generated.h"

class UGameplayEffect;

UCLASS()
class GRANDSTRATEGYGAME_API UGS_BuildingData : public UGS_BaseObjectData 
{
	GENERATED_BODY()

	UGS_BuildingData();
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGS_ProductionMethod> ProductionMethod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ConstructionAbilityTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Requirements", DisplayPriority = 0))
	TObjectPtr<URequirementsList> RequirementsList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> Effects;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGS_ProductionMethod> ConstructionMethod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayEventData> OnFinishConstructionEvents;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayEventData> OnStartConstructionEvents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayEventData> OnCancelConstructionEvents;
};
