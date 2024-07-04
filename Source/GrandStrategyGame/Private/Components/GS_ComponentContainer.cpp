
#include "Components/GS_ComponentContainer.h"

#include "BaseLibraries/GS_Library.h"
#include "BaseLibraries/GS_MathLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Map/GS_Map.h"

UGS_ComponentContainer::UGS_ComponentContainer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGS_ComponentContainer::SetTargetTransform(int32 ComponentIndex, const FTransform& NewInstanceTransform)
{
	USceneComponent* UpdatedComponent = Components[ComponentIndex];

	const FTransform OldTransform = UpdatedComponent->GetComponentTransform();
	FTransform EditableNewInstanceTransform = NewInstanceTransform;
	EditableNewInstanceTransform.SetRotation(OldTransform.GetRotation());
	TargetRotations.Add(ComponentIndex, NewInstanceTransform.Rotator());
	UpdatedComponent->SetWorldTransform(EditableNewInstanceTransform);
}

void UGS_ComponentContainer::SetTransform(int32 ComponentIndex, const FTransform& NewInstanceTransform)
{
	USceneComponent* UpdatedComponent = Components[ComponentIndex];
	UpdatedComponent->SetWorldTransform(NewInstanceTransform);
}

int32 UGS_ComponentContainer::AddComponent(USceneComponent* Component)
{
	Components.Add(Component);
	return Components.Num() - 1;
}

int32 UGS_ComponentContainer::AddActor(AActor* Actor)
{
	Components.Add(Actor->GetRootComponent());
	return Components.Num() - 1;
}

void UGS_ComponentContainer::AttachActor(AActor* Actor, int32 ComponentIndex)
{
	AttachedActors.Add(Actor, ComponentIndex);
}

void  UGS_ComponentContainer::DetachActor(AActor* Actor)
{
	AttachedActors.Remove(Actor);
}

void UGS_ComponentContainer::SnapToGrid(int32 ComponentIndex)
{
	FVector ComponentLocation = GetComponent(ComponentIndex)->GetComponentLocation();
	const FVector2D Location2D = {ComponentLocation.X, ComponentLocation.Y};
	FVector Normal;
	ComponentLocation.Z = UGS_Library::GetMap(this)->GetHeightAtLocation(Location2D, Normal);
	GetComponent(ComponentIndex)->SetWorldLocation(ComponentLocation);
	
	if(TargetRotations.Contains(ComponentIndex))
	{
		FRotator TargetRotation = TargetRotations[ComponentIndex];
		FRotator NewRotator = UGS_MathLibrary::GetRotatorFromNormalKeepYaw(TargetRotation.Yaw, Normal);
		TargetRotations.Add(ComponentIndex, NewRotator);
	}
}

void UGS_ComponentContainer::ReverseOrder()
{
	Algo::Reverse(Components);
}

void UGS_ComponentContainer::OrderAccordingToDistanceToPoint(const FVector Point, bool ClosestFirst)
{
	Algo::Sort(Components, [Point](const USceneComponent* A, const USceneComponent* B)
	{
		return FVector::Distance(A->GetComponentLocation(), Point) < FVector::Distance(B->GetComponentLocation(), Point);
	});
	if(!ClosestFirst)
	{
		ReverseOrder();
	}
}

int32 UGS_ComponentContainer::GetSize()
{
	return Components.Num();
}

void UGS_ComponentContainer::BeginPlay()
{
	Super::BeginPlay();
}

void UGS_ComponentContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for(int32 Index = 0 ; Index < Components.Num(); Index++)
	{
		SnapToGrid(Index);
	}

	for( auto[InstanceIndex, TargetRotator] : TargetRotations)
	{
		FTransform MeshTransform = Components[InstanceIndex]->GetComponentTransform();
		FRotator NewRotation = UKismetMathLibrary::RInterpTo(MeshTransform.Rotator(), TargetRotator, DeltaTime, RotationInterpolationSpeed);
		MeshTransform.SetRotation(NewRotation.Quaternion());
		Components[InstanceIndex]->SetWorldTransform(MeshTransform);
	}
	for(auto [Actor, ComponentIndex] : AttachedActors)
	{
		Actor->SetActorTransform(Components[ComponentIndex]->GetComponentTransform());
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

