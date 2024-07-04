// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GS_AbilityTask_SetFormation.generated.h"

class USplineComponent;
class UGS_ComponentContainer;

USTRUCT(BlueprintType)
struct FSetFormationMoveData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Index;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Active;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_AbilityTask_SetFormation : public UAbilityTask
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinished, int32, InstanceIndex);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInstanceReachedEnd, int32, InstanceIndex);
	
	UGS_AbilityTask_SetFormation();

	UPROPERTY(BlueprintAssignable)
	FFinished OnFinish;

	UPROPERTY(BlueprintAssignable)
	FInstanceReachedEnd OnInstanceReachedEnd;
	
	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGS_AbilityTask_SetFormation* SetFormation(UGameplayAbility* OwningAbility, FName TaskInstanceName, UGS_ComponentContainer* Components, TArray<FTransform> PositionsToReach, float Speed, float Delay, bool UseDelay = false, bool StartOnSignal = false);
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGS_AbilityTask_SetFormation* ReachPosition(UGameplayAbility* OwningAbility, FName TaskInstanceName, UGS_ComponentContainer* Components, FTransform PositionToReach, float Speed, float Delay, bool UseDelay = false, bool StartOnSignal = false);

	UFUNCTION(BlueprintCallable)
	void Restart(UGS_ComponentContainer* InComponents, TArray<FTransform> InPositionsToReach, float InSpeed, float InDelay, bool InUseDelay, bool InStartOnSignal);
	
	UFUNCTION(BlueprintCallable)
	void StartInstance(int32 Index, float inDelay, float InSpeed, bool ReconstructPath);
	
	UFUNCTION(BlueprintCallable)
	void StartAllInstances(float InDelay, float InSpeed, bool ReconstructPath);

	UFUNCTION(BlueprintCallable)
	void UpdatePositionsToReach(TArray<FTransform> NewPositions);

	void CalculateDelays();
	void CorrectStartAndEndPosition(USplineComponent* Spline, int32 Index);
	void ConstructSpline(int32 Index);
	virtual void Activate() override;
	void UpdateComponentTransform(int32 Index, FTransform NewTransform);
	float GetInstanceProgress(int32 Index);
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool AbilityIsEnding) override;

	UPROPERTY(Replicated)
	TObjectPtr<UGS_ComponentContainer> Components;

	UPROPERTY(Replicated)
	float Delay;

	UPROPERTY(Replicated)
	bool UseDelay;

	UPROPERTY(Replicated)
	TArray<FTransform> PositionsToReach;
	
	UPROPERTY(Replicated)
	float Speed;

	UPROPERTY(Replicated)
	bool StartOnSignal;
	
	UPROPERTY()
	TMap<int32, FSetFormationMoveData> InstancesData;
	
	UPROPERTY()
	TArray<USplineComponent*> Splines;

	UPROPERTY()
	TMap<AActor*, int32> AttachedActors;

	UPROPERTY()
	float TimeSinceStart = 0.0f;
	
};
