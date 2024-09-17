// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GS_ActionsManager.generated.h"

class UGS_ActionInfo;

/*USTRUCT()
struct FActionInstance
{
	GENERATED_BODY()

	FActionInstance(UGS_Action* Action, UObject* Source, UObject* Target, int32 EndTick)
		: Action(Action), Source(Source), Target(Target), EndTick(EndTick){}

	FActionInstance(){}

	UPROPERTY()
	TObjectPtr<UGS_Action> Action;

	UPROPERTY()
	TObjectPtr<UObject> Source;
	
	UPROPERTY()
	TObjectPtr<UObject> Target;

	UPROPERTY()
	int32 EndTick;

	void End();
};*/


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRANDSTRATEGYGAME_API UGS_ActionsManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGS_ActionsManager();

protected:
	virtual void BeginPlay() override;

private:
	//TArray<FActionInstance> ActionInstances;

	UFUNCTION()
	void HandleTick(int32 Tick);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
