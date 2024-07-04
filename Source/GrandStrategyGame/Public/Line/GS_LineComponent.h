// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DynamicMeshComponent.h"
#include "GS_LineComponent.generated.h"

class USplineComponent;

UCLASS(Blueprintable)
class GRANDSTRATEGYGAME_API ULineComponent : public UDynamicMeshComponent
{
	GENERATED_BODY()
	
	ULineComponent();
	
public:
	
	virtual void OnComponentCreated() override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Reset();
};
