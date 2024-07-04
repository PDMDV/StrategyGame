// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/GS_AbilityTask_GetMouseHit.h"

#include "AbilitySystemComponent.h"

UGS_AbilityTask_GetMouseHit* UGS_AbilityTask_GetMouseHit::CreateGetMouseHit(UGameplayAbility* OwningAbility, FName TaskInstanceName, bool OnlyTriggerOnce, bool SendTargetDataToServer)
{
	UGS_AbilityTask_GetMouseHit* MyObject = NewAbilityTask<UGS_AbilityTask_GetMouseHit>(OwningAbility, TaskInstanceName);

	MyObject->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObject->bTickingTask = !OnlyTriggerOnce;
	MyObject->SendTargetDataToServer = SendTargetDataToServer;

	return MyObject;
}

FGameplayAbilityTargetData_SingleTargetHit*  UGS_AbilityTask_GetMouseHit::GetHitTargetData() const
{
	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	
	if(const APlayerController* PlayerController = Ability->GetActorInfo().PlayerController.Get())
	{
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, TargetData->HitResult);
	}
	return TargetData;
}

void UGS_AbilityTask_GetMouseHit::OnTargetDataReceived(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag Tag)
{
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		MouseDataReceived.Broadcast(DataHandle);
		if(OnlyTriggerOnce)
		{
			EndTask();
		}
	}
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
}

void UGS_AbilityTask_GetMouseHit::ServerReceiveTargetData()
{
	AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey())
			.AddUObject(this, &UGS_AbilityTask_GetMouseHit::OnTargetDataReceived);
	const bool bIsCalled = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if(bIsCalled)
	{
		SetWaitingOnRemotePlayerData();
	}
}

void UGS_AbilityTask_GetMouseHit::TickTask(float DeltaTime)
{
	if(IsLocallyControlled())
	{
		SendTargetData();
	}
	else if (!IsWaitingOnRemotePlayerdata())
	{
		ServerReceiveTargetData();
	}
}

void UGS_AbilityTask_GetMouseHit::SendTargetData()
{
	FScopedPredictionWindow PredictionWindow(AbilitySystemComponent.Get());

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(GetHitTargetData());
	if(SendTargetDataToServer)
	{
		AbilitySystemComponent->ServerSetReplicatedTargetData
		(
			GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			DataHandle,
			FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey
		);
	}


	if(ShouldBroadcastAbilityTaskDelegates())
	{
		MouseDataReceived.Broadcast(DataHandle);
		if(OnlyTriggerOnce)
		{
			EndTask();
		}
	}
}

void UGS_AbilityTask_GetMouseHit::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}

void UGS_AbilityTask_GetMouseHit::BeginDestroy()
{
	Super::BeginDestroy();
}

void UGS_AbilityTask_GetMouseHit::Activate()
{
	if(IsLocallyControlled())
	{
		SendTargetData();
	}
	else
	{
		ServerReceiveTargetData();
	}
}