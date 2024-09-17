// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AttributeSets/CountryAttributeSet.h"
#include "GameFramework/Actor.h"
#include "GS_Country.generated.h"

class ULineComponent;

UCLASS()
class GRANDSTRATEGYGAME_API AGS_Country : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	AGS_Country();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> RootScene;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ULineComponent> Borders;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCountryAttributeSet> AttributeSet;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
