// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSets/CountryAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UCountryAttributeSet::OnRep_MigrationAttraction(const FGameplayAttributeData& OldMigrationAttraction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCountryAttributeSet, MigrationAttraction, OldMigrationAttraction);
}

void UCountryAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UCountryAttributeSet, MigrationAttraction, COND_None, REPNOTIFY_Always);
}