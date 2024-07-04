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

	UPROPERTY(BlueprintReadOnly, Category = "WoodsBalance", ReplicatedUsing = OnRep_WoodsBalance)
	FGameplayAttributeData WoodsBalance;
	ATTRIBUTE_ACCESSORS(USettlementAttributeSet, WoodsBalance)

	UPROPERTY(BlueprintReadOnly, Category = "PopulationGrowth", ReplicatedUsing = OnRep_PopulationGrowth)
	FGameplayAttributeData PopulationGrowth;
	ATTRIBUTE_ACCESSORS(USettlementAttributeSet, PopulationGrowth)

	UFUNCTION()
	virtual void OnRep_ConstructionSpeed(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_WoodsBalance(const FGameplayAttributeData& OldWoodsBalance);
	
	UFUNCTION()
	virtual void OnRep_PopulationGrowth(const FGameplayAttributeData& OldWPopulationGrowth);
};
