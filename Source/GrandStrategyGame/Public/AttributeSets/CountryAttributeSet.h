#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSets/GSAttributeSet.h"
#include "CountryAttributeSet.generated.h"

UCLASS()
class GRANDSTRATEGYGAME_API UCountryAttributeSet : public UGSAttributeSet
{
	GENERATED_BODY()
public: 
	UPROPERTY(BlueprintReadOnly, Category = "MigrationAttraction", ReplicatedUsing = OnRep_MigrationAttraction)
	FGameplayAttributeData MigrationAttraction;
	ATTRIBUTE_ACCESSORS(UCountryAttributeSet, MigrationAttraction)


	UFUNCTION()
	virtual void OnRep_MigrationAttraction(const FGameplayAttributeData& OldMigrationAttraction);
	
};
