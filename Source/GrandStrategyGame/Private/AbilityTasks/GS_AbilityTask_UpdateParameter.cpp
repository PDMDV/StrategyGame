// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/GS_AbilityTask_UpdateParameter.h"

UGS_AbilityTask_UpdateParameter::UGS_AbilityTask_UpdateParameter()
{
	bTickingTask = true;
	bSimulatedTask = true;
}

void UGS_AbilityTask_UpdateParameter::InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent)
{
	Super::InitSimulatedTask(InGameplayTasksComponent);
}

UGS_AbilityTask_UpdateParameter* UGS_AbilityTask_UpdateParameter::UpdateMaterialScalarParameter(UGameplayAbility* OwningAbility,  FName TaskInstanceName, FName ParameterName, UMaterialInstanceDynamic* MaterialInstance, UObject* Object, FName FunctionName)
{
	UGS_AbilityTask_UpdateParameter* MyObj = NewAbilityTask<UGS_AbilityTask_UpdateParameter>(OwningAbility, TaskInstanceName);
	
	MyObj->ParameterName = ParameterName;
	MyObj->Object = Object;
	MyObj->FunctionName = FunctionName;
	MyObj->MaterialInstance = MaterialInstance;
	
	return MyObj;
}

void UGS_AbilityTask_UpdateParameter::Activate()
{
	Super::Activate();

	Function = Object->FindFunction(FunctionName);
}

void UGS_AbilityTask_UpdateParameter::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	if(Object->IsValidLowLevelFast())
	{
		Object->ProcessEvent(Function, &Value);
		MaterialInstance->SetScalarParameterValue(ParameterName, Value);
	}

}


