// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GS_ActionDataAsset.generated.h"

class UGS_ActionInfo;
/**
 * 
 */
UCLASS()
class GRANDSTRATEGYGAME_API UGS_ActionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Action", DisplayPriority = 0))
	TObjectPtr<UGS_ActionInfo> Action;
	
};
