#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_BaseObjectData.h"
#include "Goods/GS_GoodsLibrary.h"
#include "GS_UnitData.generated.h"

class UGS_PopData;

UCLASS(BlueprintType)
class GRANDSTRATEGYGAME_API UGS_UnitData : public UGS_BaseObjectData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGoodsContainer RecruitmentGoods;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGoodsContainer UpkeepGoods;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Salary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UGS_PopData> RequiredPopType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Size = 100;
};
