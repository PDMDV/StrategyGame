// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSets/SettlementAttributeSet.h"

#include "Net/UnrealNetwork.h"

void USettlementAttributeSet::OnRep_ConstructionSpeed(const FGameplayAttributeData& OldConstructionSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USettlementAttributeSet, ConstructionSpeed, OldConstructionSpeed);
}

void USettlementAttributeSet::OnRep_WoodsBalance(const FGameplayAttributeData& OldWoodsBalance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USettlementAttributeSet, WoodsBalance, OldWoodsBalance);
}

void USettlementAttributeSet::OnRep_PopulationGrowth(const FGameplayAttributeData& OldPopulationGrowth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USettlementAttributeSet, PopulationGrowth, OldPopulationGrowth);
}

void USettlementAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	GetConstructionSpeedAttribute();

	DOREPLIFETIME_CONDITION_NOTIFY(USettlementAttributeSet, ConstructionSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USettlementAttributeSet, WoodsBalance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USettlementAttributeSet, PopulationGrowth, COND_None, REPNOTIFY_Always);
}
