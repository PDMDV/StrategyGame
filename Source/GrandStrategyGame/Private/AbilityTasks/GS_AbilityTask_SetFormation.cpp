// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/GS_AbilityTask_SetFormation.h"

#include "BaseLibraries/GS_Library.h"
#include "Components/GS_ComponentContainer.h"
#include "Components/SplineComponent.h"
#include "MuR/Instance.h"
#include "Net/UnrealNetwork.h"

UGS_AbilityTask_SetFormation::UGS_AbilityTask_SetFormation()
{
	bTickingTask = true;
	bSimulatedTask = true;
}

void UGS_AbilityTask_SetFormation::InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent)
{
	Super::InitSimulatedTask(InGameplayTasksComponent);
}

UGS_AbilityTask_SetFormation* UGS_AbilityTask_SetFormation::SetFormation(UGameplayAbility* OwningAbility, FName TaskInstanceName, UGS_ComponentContainer* Components, TArray<FTransform> PositionsToReach, float Speed, float Delay, bool UseDelay, bool StartOnSignal)
{
	UGS_AbilityTask_SetFormation* MyObj = NewAbilityTask<UGS_AbilityTask_SetFormation>(OwningAbility, TaskInstanceName);
	
	MyObj->Components = Components;
	MyObj->Delay = Delay;
	MyObj->UseDelay = UseDelay;
	MyObj->PositionsToReach = PositionsToReach;
	MyObj->Speed = Speed;
	MyObj->StartOnSignal = StartOnSignal;
	
	return MyObj;
}

UGS_AbilityTask_SetFormation* UGS_AbilityTask_SetFormation::ReachPosition(UGameplayAbility* OwningAbility,FName TaskInstanceName, UGS_ComponentContainer* Components, FTransform PositionToReach, float Speed, float Delay,bool UseDelay, bool StartOnSignal)
{
	TArray<FTransform> PositionsToReach;
	PositionsToReach.Init(PositionToReach, Components->GetSize());
	return SetFormation(OwningAbility, TaskInstanceName, Components, PositionsToReach, Speed, Delay, UseDelay, StartOnSignal);
}

void UGS_AbilityTask_SetFormation::Restart(UGS_ComponentContainer* InComponents, TArray<FTransform> InPositionsToReach, float InSpeed, float InDelay, bool InUseDelay, bool InStartOnSignal)
{
	this->Components = InComponents;
	this->Delay = InDelay;
	this->UseDelay = InUseDelay;
	this->PositionsToReach = InPositionsToReach;
	this->Speed = InSpeed;
	this->StartOnSignal = InStartOnSignal;

	TimeSinceStart = 0.0f;
	
	Activate();
}

void UGS_AbilityTask_SetFormation::StartInstance(int32 Index, float inDelay, float InSpeed, bool ReconstructPath)
{
	InstancesData[Index] = {Index,true,inDelay + TimeSinceStart,InSpeed};
	if(ReconstructPath)
	{ 
		ConstructSpline(Index);
	}
}

void UGS_AbilityTask_SetFormation::StartAllInstances(float InDelay, float InSpeed, bool ReconstructPath)
{
	for(TPair<int32, FSetFormationMoveData> Instance : InstancesData.Array())
	{
		StartInstance(Instance.Key, InDelay, InSpeed, ReconstructPath);
	}
}

void UGS_AbilityTask_SetFormation::UpdatePositionsToReach(TArray<FTransform> NewPositions)
{
	PositionsToReach = NewPositions;
}

void UGS_AbilityTask_SetFormation::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(UGS_AbilityTask_SetFormation, Components);
	DOREPLIFETIME(UGS_AbilityTask_SetFormation, Delay);
	DOREPLIFETIME(UGS_AbilityTask_SetFormation, UseDelay);
	DOREPLIFETIME(UGS_AbilityTask_SetFormation, PositionsToReach);
	DOREPLIFETIME(UGS_AbilityTask_SetFormation, Speed);
}

void UGS_AbilityTask_SetFormation::CalculateDelays()
{
	TArray<TPair<int32, float>> DistanceToEnd;

	int32 Index = 0;
	for(USplineComponent* Spline : Splines)
	{
		DistanceToEnd.Add({Index++, Spline->GetSplineLength()});
	}
	//Algo::Sort(DistanceToEnd,[](TPair<int32, float> A, TPair<int32, float> B){return A.Value < B.Value;});
	
	float PreviousInstanceReachTime = -Delay;
	
	for(auto Pair : DistanceToEnd)
	{
		Index = Pair.Key;
		
		float TimeToReachEnd = Pair.Value / Speed;
		InstancesData[Index].StartDelay = FMath::Max(PreviousInstanceReachTime + Delay - TimeToReachEnd, 0);
		PreviousInstanceReachTime = InstancesData[Index].StartDelay + TimeToReachEnd;
	}
}

void UGS_AbilityTask_SetFormation::CorrectStartAndEndPosition(USplineComponent* Spline, int32 Index)
{
	const FVector FirstTangent = Spline->GetTangentAtSplinePoint(0, ESplineCoordinateSpace::Local);
	const FVector NewFirstTangent = Components->GetComponent(Index)->GetComponentTransform().GetRotation().Vector() * FirstTangent.Length();
	Spline->SetTangentAtSplinePoint(0, NewFirstTangent, ESplineCoordinateSpace::Local);

	const int32 LastTangentIndex = Spline->GetNumberOfSplinePoints() - 1;
	const FVector LastTangent = Spline->GetTangentAtSplinePoint(LastTangentIndex, ESplineCoordinateSpace::Local);
	const FVector NewLastTangent = PositionsToReach[Index].GetRotation().Vector() * LastTangent.Length();
	Spline->SetTangentAtSplinePoint(LastTangentIndex, NewLastTangent, ESplineCoordinateSpace::Local);
}

void UGS_AbilityTask_SetFormation::ConstructSpline(int32 Index)
{
	FTransform ComponentTransform = Components->GetComponent(Index)->GetComponentTransform();
	Splines[Index]->SetWorldLocation(ComponentTransform.GetLocation());
	Splines[Index]->ClearSplinePoints();

	Splines[Index]->AddSplinePoint(ComponentTransform.GetLocation(), ESplineCoordinateSpace::World, true);
	Splines[Index]->AddSplinePoint(PositionsToReach[Index].GetLocation(), ESplineCoordinateSpace::World, true);
		
	CorrectStartAndEndPosition(Splines[Index], Index);
	UGS_Library::CorrectSpline(Splines[Index]);
}

void UGS_AbilityTask_SetFormation::Activate()
{
	Super::Activate();
	InstancesData.Empty();
	Splines.Empty();
	for(int32 Index = 0 ; Index < Components->GetSize() ; Index++)
	{
		InstancesData.Add(Index, {Index,!StartOnSignal, 0.0f,Speed});
		
		Splines.Add(Cast<USplineComponent>(GetOwnerActor()->AddComponentByClass(USplineComponent::StaticClass(), true, FTransform(), true)));
		ConstructSpline(Index);
	}
	if(UseDelay)
	{
		CalculateDelays();
	}
}

void UGS_AbilityTask_SetFormation::UpdateComponentTransform(int32 Index, FTransform NewTransform)
{
	Components->SetTargetTransform(Index, NewTransform);
}

float UGS_AbilityTask_SetFormation::GetInstanceProgress(int32 Index)
{
	return (TimeSinceStart - InstancesData[Index].StartDelay) * Speed;
}

void UGS_AbilityTask_SetFormation::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	TimeSinceStart += DeltaTime;

	int IndexToRemove = -1;
	for(TPair<int32, FSetFormationMoveData> Data : InstancesData)
	{
		FSetFormationMoveData InstanceData = Data.Value;
		const int32 Index = Data.Key;

		if(!InstanceData.Active) continue;
		
		FTransform InstanceTransform = Components->GetComponent(Index)->GetComponentTransform();
		
		const float InstanceProgress = GetInstanceProgress(Index);
		if(InstanceProgress > 0.f)
		{
			FTransform NewTransform = Splines[Index]->GetTransformAtDistanceAlongSpline(InstanceProgress, ESplineCoordinateSpace::World);
		
			// Set Z value from instance Transform
			FVector ModifyZ = NewTransform.GetLocation();
			ModifyZ.Z = InstanceTransform.GetLocation().Z;
			NewTransform.SetLocation(ModifyZ);

			UpdateComponentTransform(Index, NewTransform);

			if(InstanceProgress > Splines[Index]->GetSplineLength())
			{
				const FTransform FinalTransform = Splines[Index]->GetTransformAtSplinePoint(Splines[Index]->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
				UpdateComponentTransform(Index, FinalTransform);
				IndexToRemove = Index;
				OnInstanceReachedEnd.Broadcast(Index);
			}
		}
	}
	if(IndexToRemove != -1)
	{
		InstancesData.Remove(IndexToRemove);
	}
	
	if(InstancesData.IsEmpty())
	{
		OnFinish.Broadcast(0);
		//EndTask();
	} 
}

void UGS_AbilityTask_SetFormation::OnDestroy(bool AbilityIsEnding)
{
	Super::OnDestroy(AbilityIsEnding);
	for(USplineComponent* Spline : Splines)
	{
		if(Spline)
		{
			Spline->DestroyComponent();
		}
	}
	Super::OnDestroy(AbilityIsEnding);
}
