// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BaseData/GS_BaseObjectData.h"
#include "BaseData/GS_ProductionMethod.h"
#include "GS_BuildingData.generated.h"

class UGS_Cost;
class URequirement;
class UGS_EffectInfo;
class UGameplayEffect;

UCLASS()
class GRANDSTRATEGYGAME_API UGS_BuildingData : public UGS_BaseObjectData 
{
	GENERATED_BODY()

	UGS_BuildingData();
public:

	UFUNCTION(BlueprintPure)
	bool CanBeBuild(UObject* Target);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGS_ProductionMethod> ProductionMethod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ConstructionAbilityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag UpgradeAbilityTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Requirements", DisplayPriority = 0))
	TArray<TObjectPtr<URequirement>> Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Costs", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_Cost>> ConstructionCosts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Effects", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_EffectInfo>> FinishEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UGS_BuildingData> Upgrade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UGS_BuildingData> Downgrade;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UGS_ProductionMethod> ConstructionMethod;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayEventData> OnFinishConstructionEvents;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayEventData> OnStartConstructionEvents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameplayEventData> OnCancelConstructionEvents;
};
