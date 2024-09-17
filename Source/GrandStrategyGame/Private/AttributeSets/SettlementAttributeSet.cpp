// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSets/SettlementAttributeSet.h"

#include "Net/UnrealNetwork.h"

void USettlementAttributeSet::OnRep_ConstructionSpeed(const FGameplayAttributeData& OldConstructionSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USettlementAttributeSet, ConstructionSpeed, OldConstructionSpeed);
}

void USettlementAttributeSet::OnRep_MigrationAttraction(const FGameplayAttributeData& OldMigrationAttraction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USettlementAttributeSet, MigrationAttraction, OldMigrationAttraction);
}

void USettlementAttributeSet::OnRep_PopulationGrowth(const FGameplayAttributeData& OldPopulationGrowth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USettlementAttributeSet, PopulationGrowth, OldPopulationGrowth);
}

void USettlementAttributeSet::OnRep_PopulationCapacity(const FGameplayAttributeData& OldPopulationCapacity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USettlementAttributeSet, PopulationCapacity, OldPopulationCapacity);
}

void USettlementAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USettlementAttributeSet, ConstructionSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USettlementAttributeSet, MigrationAttraction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USettlementAttributeSet, PopulationGrowth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USettlementAttributeSet, PopulationCapacity, COND_None, REPNOTIFY_Always);
}
