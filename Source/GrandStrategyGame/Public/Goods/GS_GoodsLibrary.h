
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Province/Data/GS_GoodData.h"
#include "GS_GoodsLibrary.generated.h"

USTRUCT(BlueprintType)
struct FGoods
{
	GENERATED_BODY()

	FGoods() {};
	FGoods(const TObjectPtr<UGS_GoodData>& ResourceData) : GoodData(ResourceData){};

	friend bool operator==(const FGoods& Lhs, const FGoods& RHS)
	{
		return Lhs.GoodData == RHS.GoodData;
	}

	friend bool operator!=(const FGoods& Lhs, const FGoods& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGS_GoodData> GoodData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount = 0;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_GoodsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
