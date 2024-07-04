// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Requirements/RequirementComponent.h"
#include "Or.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GRANDSTRATEGYGAME_API UOr : public URequirementComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Or", DisplayPriority = 0))
	TArray<TObjectPtr<URequirementComponent>> OrList;
	
	virtual bool IsCompliant(UObject* Source, UObject* Target);
	
};
