// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GS_AbilityTask_GetMouseHit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataDelegate, const FGameplayAbilityTargetDataHandle&, Data);

UCLASS()
class GRANDSTRATEGYGAME_API UGS_AbilityTask_GetMouseHit : public UAbilityTask
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, meta=(DisplayName = "GetMouseHit" ,HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"), Category="Ability|Tasks")
	static UGS_AbilityTask_GetMouseHit* CreateGetMouseHit(UGameplayAbility* OwningAbility, FName TaskInstanceName, bool OnlyTriggerOnce = true, bool SendTargetDataToServer = true);
	
	UPROPERTY(BlueprintAssignable)
	FTargetDataDelegate MouseDataReceived;

	bool OnlyTriggerOnce = true;
	bool SendTargetDataToServer = true;
	
private:
	
	FGameplayAbilityTargetData_SingleTargetHit*  GetHitTargetData() const;
	void OnTargetDataReceived(const FGameplayAbilityTargetDataHandle&, FGameplayTag);
	void ServerReceiveTargetData();
	void SendTargetData();
	
protected:
	
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	virtual void BeginDestroy() override;
	virtual void Activate() override;
};