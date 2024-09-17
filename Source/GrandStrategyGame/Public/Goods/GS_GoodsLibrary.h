#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_ContainerTemplate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Province/Data/GS_GoodData.h"
#include "GS_GoodsLibrary.generated.h"

USTRUCT(BlueprintType)
struct FGoods
{
	GENERATED_BODY()

	FGoods() {};
	FGoods(UGS_GoodData* ResourceData) : Type(ResourceData){};
	FGoods(UGS_GoodData* ResourceData, const float Amount ) : Type(ResourceData), Amount(Amount) {};

	friend bool operator==(const FGoods& Lhs, const FGoods& RHS)
	{
		return Lhs.Type == RHS.Type;
	}

	friend bool operator!=(const FGoods& Lhs, const FGoods& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGS_GoodData* Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount = 0;
};

USTRUCT(BlueprintType)
struct FGoodsContainer
{
	GENERATED_BODY()
	
	TArray<FGoods>& GetArray(){ return Goods; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGoods> Goods;
}; 

UCLASS()
class GRANDSTRATEGYGAME_API UGS_GoodsLibrary : public UBlueprintFunctionLibrary, public TContainerFunctions<FGoodsContainer, FGoods>
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	static int32 FindIndex(UPARAM(ref) FGoodsContainer& Container, UGS_GoodData* Object);

	UFUNCTION(BlueprintCallable)
	static void Add(UPARAM(ref) FGoodsContainer& Container, FGoods Element);

	UFUNCTION(BlueprintCallable)
	static float Subtract(UPARAM(ref) FGoodsContainer& Container, FGoods Element);

	UFUNCTION(BlueprintCallable)
	static void Merge(UPARAM(ref) FGoodsContainer& Target, UPARAM(ref) FGoodsContainer& Source);
	
	UFUNCTION(BlueprintPure)
    static FGoodsContainer Combine(UPARAM(ref) FGoodsContainer& First, UPARAM(ref) FGoodsContainer& Second);

	UFUNCTION(BlueprintCallable)
	static void Clear(UPARAM(ref) FGoodsContainer& Container);

	UFUNCTION(BlueprintPure)
	static FGoods Get(UPARAM(ref) FGoodsContainer& Container, UGS_GoodData* Type);

	UFUNCTION(BlueprintPure)
	static FGoods Multiply(FGoods Struct, float Multiplier);
	
	UFUNCTION(BlueprintPure)
	static FGoodsContainer MultiplyContainer(UPARAM(ref)FGoodsContainer& Container, float Multiplier);

	UFUNCTION(BlueprintPure)
	static bool HasType(UPARAM(ref) FGoodsContainer& Container, UGS_GoodData* Type);

	UFUNCTION(BlueprintPure)
	static bool Contains(UPARAM(ref) FGoodsContainer& Source, UPARAM(ref) FGoodsContainer& Target);

	UFUNCTION(BlueprintPure)
	static TArray<UGS_GoodData*> GetAllTypes(UPARAM(ref) FGoodsContainer& Container);

	UFUNCTION(BlueprintPure)
	static TSet<UGS_GoodData*> GetAllTypesSet(UPARAM(ref) FGoodsContainer& Container);

	UFUNCTION(BlueprintPure)
	static float GetTotalSize(UPARAM(ref) FGoodsContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static FGoodsContainer Negate(UPARAM(ref) FGoodsContainer& Container);

	UFUNCTION(BlueprintPure)
	static bool IsEmpty(UPARAM(ref) FGoodsContainer& Container);

	UFUNCTION(BlueprintPure)
	static bool IsNotEmpty(UPARAM(ref) FGoodsContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static FGoodsContainer MakeContainer(const FGoods& Element);
};
