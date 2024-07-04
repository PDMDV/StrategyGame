// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GS_GameState.h"

#include "AbilitySystemComponent.h"

AGS_GameState::AGS_GameState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* AGS_GameState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
