// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GS_AbilityTask_GameTick.generated.h"

UENUM(BlueprintType)
enum class TickType : uint8 {
	Daily UMETA(DisplayName = "Daily"),
	Weekly UMETA(DisplayName = "Weekly"),
	Monthly UMETA(DisplayName = "Monthly"),
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_AbilityTask_GameTick : public UAbilityTask
{
	GENERATED_BODY()
	
	/*UGS_AbilityTask_GameTick();
	
	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGS_AbilityTask_UpdateParameter* GameTick(UGameplayAbility* OwningAbility, FName TaskInstanceName, TickType TickType);*/
	
};
