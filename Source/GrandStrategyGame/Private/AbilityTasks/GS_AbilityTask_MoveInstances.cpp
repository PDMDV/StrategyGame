#include "AbilityTasks\GS_AbilityTask_MoveInstances.h"

#include "BaseLibraries/GS_Library.h"
#include "Components/GS_ComponentContainer.h"
#include "Components/SplineComponent.h"
#include "Net/UnrealNetwork.h"

UGS_AbilityTask_MoveInstances::UGS_AbilityTask_MoveInstances()
{
	bTickingTask = true;
	bSimulatedTask = true;
}

void UGS_AbilityTask_MoveInstances::InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent)
{
	Super::InitSimulatedTask(InGameplayTasksComponent);
}

UGS_AbilityTask_MoveInstances* UGS_AbilityTask_MoveInstances::MoveInstancesAlongPath(UGameplayAbility* OwningAbility, FName TaskInstanceName, UGS_ComponentContainer* Components, const TArray<FVector> Path, bool StartOnSignal, float Speed)
{
	UGS_AbilityTask_MoveInstances* MyObj = NewAbilityTask<UGS_AbilityTask_MoveInstances>(OwningAbility, TaskInstanceName);
	
	MyObj->Components = Components;
	MyObj->Path = Path;
	MyObj->StartOnSignal = StartOnSignal;
	MyObj->Speed = Speed;
	
	return MyObj;
}

void UGS_AbilityTask_MoveInstances::StopAllInstances()
{
	for(int32 Index = 0; Index < Components->GetSize(); Index++)
	{
		InstancesData[Index].Active = false;
	}
}

void UGS_AbilityTask_MoveInstances::StartInstance(int32 Index, float Delay, float InSpeed)
{
	InstancesData[Index] = {Index,true,Delay + TimeSinceStart,InSpeed};
}

void UGS_AbilityTask_MoveInstances::UpdatePath(TArray<FVector> NewPath)
{
	if(NewPath.IsEmpty()) return;

	TimeSinceStart = 0.0f;
	MaxProgress = 0.0f;
	NextPathPointIndex = 0;
	
	Path = NewPath;
	Spline->SetWorldLocation(Path[0]);
	Spline->ClearSplinePoints();

	for(FVector Position  : Path )
	{
		Spline->AddSplinePoint(Position, ESplineCoordinateSpace::World, true);
	}
	
	UGS_Library::CorrectSpline(Spline);
}

FTransform UGS_AbilityTask_MoveInstances::GetSplinePointTransform(int32 Index)
{
	return Spline->GetTransformAtSplinePoint(Index, ESplineCoordinateSpace::World);
}

float UGS_AbilityTask_MoveInstances::GetMaxProgressPercentage()
{
	return MaxProgress / Spline->GetSplineLength();
}

void UGS_AbilityTask_MoveInstances::SetPause(bool InPause)
{
	Pause = InPause;
} 

FTransform UGS_AbilityTask_MoveInstances::GetLastReachedPointPosition()
{
	return Spline->GetTransformAtSplinePoint(NextPathPointIndex - 1, ESplineCoordinateSpace::World);
}

void UGS_AbilityTask_MoveInstances::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(UGS_AbilityTask_MoveInstances, Components);
}

void UGS_AbilityTask_MoveInstances::Activate()
{
	Super::Activate();

	for(int32 Index = 0; Index < Components->GetSize(); Index++)
	{
		InstancesData.Add(Index, {Index,!StartOnSignal,0.0f, Speed});
	}

	Spline = Cast<USplineComponent>(GetOwnerActor()->AddComponentByClass(USplineComponent::StaticClass(), true, FTransform(), true));
	UpdatePath(Path);
	
	UGS_Library::CorrectSpline(Spline);
}

void UGS_AbilityTask_MoveInstances::UpdateComponentTransform(int32 Index, FTransform NewTransform)
{
	Components->SetTargetTransform(Index, NewTransform);
}

float UGS_AbilityTask_MoveInstances::GetInstanceProgress(int32 Index)
{
	float DelayTime = InstancesData[Index].StartDelay;
	return (TimeSinceStart - DelayTime) * Speed;
}

void UGS_AbilityTask_MoveInstances::TickTask(float DeltaTime)
{
	if(Pause) return;
	Super::TickTask(DeltaTime);
	TimeSinceStart += DeltaTime;

	int IndexToRemove = -1;
	for(const TPair<int32, FMoveData> Data : InstancesData)
	{
		FMoveData InstanceData = Data.Value;
		int32 Index = Data.Key;
		
		if (!InstanceData.Active) continue;
		
		FTransform InstanceTransform = Components->GetComponent(Index)->GetComponentTransform();
		
		const float InstanceProgress = GetInstanceProgress(Index);
		if(InstanceProgress > 0.f && InstanceProgress)
		{
			FTransform NewTransform = Spline->GetTransformAtDistanceAlongSpline(InstanceProgress, ESplineCoordinateSpace::World);
		
			// Set Z value from instance Transform
			FVector ModifyZ = NewTransform.GetLocation();
			ModifyZ.Z = InstanceTransform.GetLocation().Z;
			NewTransform.SetLocation(ModifyZ);

			UpdateComponentTransform(Index, NewTransform);

			if(InstanceProgress > Spline->GetSplineLength())
			{
				const FTransform FinalTransform = Spline->GetTransformAtSplinePoint(Spline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
				UpdateComponentTransform(Index, FinalTransform);
				IndexToRemove = Index;
			}
			if(InstanceProgress > Spline->GetDistanceAlongSplineAtSplinePoint(NextPathPointIndex) && NextPathPointIndex < Spline->GetNumberOfSplinePoints())
			{
				NextPathPointIndex++;
				OnPathPointReached.Broadcast(Index);
			}

			MaxProgress = FMath::Max(InstanceProgress, MaxProgress);
		}
	}
	
	if(IndexToRemove != -1)
	{
		InstancesData.Remove(IndexToRemove);
		OnInstanceReachedEnd.Broadcast(IndexToRemove);
	}
	
	if(InstancesData.IsEmpty())
	{
		OnAllInstancedReachedEnd.Broadcast(IndexToRemove);
		EndTask();
	}
}

void UGS_AbilityTask_MoveInstances::OnDestroy(bool AbilityIsEnding)
{
	if(Spline)
    {
        Spline->DestroyComponent();
    }
	Super::OnDestroy(AbilityIsEnding);
}