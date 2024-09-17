#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GSAttributeSet.h"
#include "SettlementAttributeSet.generated.h"

UCLASS()
class GRANDSTRATEGYGAME_API USettlementAttributeSet : public UGSAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "ConstructionSpeed", ReplicatedUsing = OnRep_ConstructionSpeed)
	FGameplayAttributeData ConstructionSpeed;
	ATTRIBUTE_ACCESSORS(USettlementAttributeSet, ConstructionSpeed)
	
	UPROPERTY(BlueprintReadOnly, Category = "MigrationAttraction", ReplicatedUsing = OnRep_MigrationAttraction)
	FGameplayAttributeData MigrationAttraction;
	ATTRIBUTE_ACCESSORS(USettlementAttributeSet, MigrationAttraction)

	UPROPERTY(BlueprintReadOnly, Category = "PopulationGrowth", ReplicatedUsing = OnRep_PopulationGrowth)
	FGameplayAttributeData PopulationGrowth;
	ATTRIBUTE_ACCESSORS(USettlementAttributeSet, PopulationGrowth)
	
	UPROPERTY(BlueprintReadOnly, Category = "PopulationCapacity", ReplicatedUsing = OnRep_PopulationCapacity)
	FGameplayAttributeData PopulationCapacity;
	ATTRIBUTE_ACCESSORS(USettlementAttributeSet, PopulationCapacity)

	UFUNCTION()
	virtual void OnRep_ConstructionSpeed(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MigrationAttraction(const FGameplayAttributeData& OldMigrationAttraction);
	
	UFUNCTION()
	virtual void OnRep_PopulationGrowth(const FGameplayAttributeData& OldWPopulationGrowth);
	
	UFUNCTION()
	virtual void OnRep_PopulationCapacity(const FGameplayAttributeData& OldPopulationCapacity);
};
