// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GS_AbilityTask_MoveInstances.generated.h"

class USplineComponent;

USTRUCT(BlueprintType)
struct FMoveData
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
class GRANDSTRATEGYGAME_API UGS_AbilityTask_MoveInstances : public UAbilityTask
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInstanceReachedEnd, int32, InstanceIndex);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllInstanceReachedPoint, int32, InstanceIndex);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPathPointReached, int32, InstanceIndex);
	
	UGS_AbilityTask_MoveInstances();

	UPROPERTY(BlueprintAssignable)
	FAllInstanceReachedPoint OnAllInstancedReachedEnd;

	UPROPERTY(BlueprintAssignable)
	FOnPathPointReached OnPathPointReached;

	UPROPERTY(BlueprintAssignable)
	FInstanceReachedEnd OnInstanceReachedEnd;
	
	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGS_AbilityTask_MoveInstances* MoveInstancesAlongPath(UGameplayAbility* OwningAbility, FName TaskInstanceName, UGS_ComponentContainer* Components, const TArray<FVector> Path, bool StartOnSignal, float Speed);

	UFUNCTION(BlueprintCallable)
	void StopAllInstances();
	
	UFUNCTION(BlueprintCallable)
	void StartInstance(int32 Index, float Delay, float InSpeed);

	UFUNCTION(BlueprintCallable)
	void UpdatePath(TArray<FVector> NewPath);

	UFUNCTION(BlueprintPure)
	FTransform GetSplinePointTransform(int32 Index);

	UFUNCTION(BlueprintPure)
	float GetMaxProgressPercentage();

	UFUNCTION(BlueprintCallable)
	void SetPause(bool InPause);

	UFUNCTION(BlueprintPure)
	FTransform GetLastReachedPointPosition();

	virtual void Activate() override;
	void UpdateComponentTransform(int32 Index, FTransform NewTransform);
	float GetInstanceProgress(int32 Index);
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool AbilityIsEnding) override;

	UPROPERTY(Replicated)
	TObjectPtr<UGS_ComponentContainer> Components;

	UPROPERTY(Replicated)
	TArray<FVector> Path;

	UPROPERTY(Replicated)
	bool StartOnSignal;

	UPROPERTY(Replicated)
	float Speed;

	UPROPERTY(Replicated)
	bool Pause;

	UPROPERTY()
	TMap<int32, FMoveData> InstancesData;
	
	UPROPERTY()
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY()
	TMap<AActor*, int32> AttachedActors;

	UPROPERTY()
	float MaxProgress = 0.f;

	UPROPERTY()
	int32 NextPathPointIndex;

	UPROPERTY()
	float TimeSinceStart = 0.0f;
};
