// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GS_AbilityTask_UpdateParameter.generated.h"

/**
 * 
 */
UCLASS()
class GRANDSTRATEGYGAME_API UGS_AbilityTask_UpdateParameter : public UAbilityTask
{
	GENERATED_BODY()
	
	UGS_AbilityTask_UpdateParameter();

	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGS_AbilityTask_UpdateParameter* UpdateMaterialScalarParameter(UGameplayAbility* OwningAbility, FName TaskInstanceName, FName ParameterName, UMaterialInstanceDynamic* MaterialInstance, UObject* Object, FName FunctionName);

	virtual void TickTask(float DeltaTime) override;
	virtual void Activate() override;
	
	UPROPERTY()
	UFunction* Function;
	
	UPROPERTY()
	FName ParameterName;

	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance;
	
	UPROPERTY()
	UObject* Object;

	UPROPERTY()
	FName FunctionName;

	UPROPERTY()
	float Value;
};
