// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GS_TickManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTick, int32, Tick);


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRANDSTRATEGYGAME_API UGS_TickManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGS_TickManager();

	UFUNCTION(BlueprintCallable)
	void SetPause(bool Paused) { IsPaused = Paused; };

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	int32 TicksNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TickTime = 1.f;

	UPROPERTY()
	float TimeFromLastTick = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPaused = true;
	
	UPROPERTY(BlueprintAssignable)
	FOnTick OnTick;
};
