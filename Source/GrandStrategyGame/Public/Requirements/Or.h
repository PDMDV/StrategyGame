// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Requirements/Requirement.h"
#include "Or.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GRANDSTRATEGYGAME_API UOr : public URequirement
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, meta = (DisplayName = "Or", DisplayPriority = 0))
	TArray<TObjectPtr<URequirement>> OrList;
	
	virtual bool IsCompliant(UObject* Source, UObject* Target);
	
};
