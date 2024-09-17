// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GS_GameState.h"

#include "AbilitySystemComponent.h"
#include "Game/GS_TickManager.h"
#include "Managers/GS_ActionsManager.h"

AGS_GameState::AGS_GameState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);

	TickManagerNew = CreateDefaultSubobject<UGS_TickManager>(TEXT("Tick Manager New"));
	ActionsManager = CreateDefaultSubobject<UGS_ActionsManager>(TEXT("Actions Manager"));
}

UAbilitySystemComponent* AGS_GameState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
