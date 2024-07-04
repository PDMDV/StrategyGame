#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GS_ComponentContainer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class GRANDSTRATEGYGAME_API UGS_ComponentContainer : public USceneComponent
{
	GENERATED_BODY()

public:	
	UGS_ComponentContainer();
	
	UFUNCTION(BlueprintCallable)
	virtual void SetTargetTransform(int32 ComponentIndex, const FTransform& NewInstanceTransform);

	UFUNCTION(BlueprintCallable)
	virtual void SetTransform(int32 ComponentIndex, const FTransform& NewInstanceTransform);

	UFUNCTION(BlueprintCallable)
	virtual int32 AddComponent(USceneComponent* Component);
	
	UFUNCTION(BlueprintCallable)
	virtual int32 AddActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	virtual void AttachActor(AActor* Actor, int32 ComponentIndex);

	UFUNCTION(BlueprintCallable)
	virtual void DetachActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	virtual void SnapToGrid(int32 ComponentIndex);

	UFUNCTION(BlueprintCallable)
	virtual void ReverseOrder();
	
	UFUNCTION(BlueprintCallable)
	virtual void OrderAccordingToDistanceToPoint(const FVector Point, bool ClosestFirst);
	
	UFUNCTION(BlueprintPure)
	virtual USceneComponent* GetComponent(const int32 ComponentIndex) { return Components[ComponentIndex]; }

	UFUNCTION(BlueprintPure)
	virtual int32 GetSize();
	
	UFUNCTION(BlueprintPure)
	virtual TArray<USceneComponent*> GetComponents() {return Components;}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationInterpolationSpeed = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<USceneComponent*> Components;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<int32, FRotator> TargetRotations;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<AActor*, int32> AttachedActors;
};
