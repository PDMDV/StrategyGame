// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/GameStateBase.h"
#include "GS_GameState.generated.h"

class UGS_MapData;

UCLASS()
class GRANDSTRATEGYGAME_API AGS_GameState : public AGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

	AGS_GameState();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGS_MapData* MapDataAsset;
	
};
