// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "GS_Region.generated.h"

class USettlementAttributeSet;

UCLASS()
class GRANDSTRATEGYGAME_API AGS_Region : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AGS_Region();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USettlementAttributeSet> AttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void BeginPlay() override;

};
