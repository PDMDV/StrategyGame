#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "BaseData/GS_Object.h"
#include "GS_Building.generated.h"

class UGS_EffectInstance;
class UGS_BuildingData;

UCLASS(BlueprintType, Blueprintable)
class GRANDSTRATEGYGAME_API UGS_Building : public UGS_Object
{
	GENERATED_BODY()
	 
public:

	UFUNCTION(BlueprintCallable)
	static UGS_Building* CreateBuilding(UGS_BuildingData* BuildingType, int32 Level, int32 Mark, UObject* Outer, TSubclassOf<UGS_Building> Class);

	UFUNCTION(BlueprintCallable)
	void ChangeLevelBy(int32 Value);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UGS_BuildingData> BuildingData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Efficiency = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Mark = 0;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<UGS_EffectInstance*> EffectInstances;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FActiveGameplayEffectHandle GameplayEffectHandle;
};
