#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_ContainerTemplate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_PopLibrary.generated.h"

class UGS_PopData;

USTRUCT(BlueprintType)
struct FPop
{
	GENERATED_BODY()

	FPop() {};
	FPop(UGS_PopData* ResourceData) : Type(ResourceData){};
	FPop(UGS_PopData* ResourceData, const int32 Amount ) : Type(ResourceData), Amount(Amount) {};

	friend bool operator==(const FPop& Lhs, const FPop& RHS)
	{
		return Lhs.Type == RHS.Type;
	}

	friend bool operator!=(const FPop& Lhs, const FPop& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGS_PopData* Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};

USTRUCT(BlueprintType)
struct FPopContainer
{
	GENERATED_BODY()

	TArray<FPop>& GetArray(){ return Pops; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPop> Pops;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_PopLibrary : public UBlueprintFunctionLibrary, public TContainerFunctions<FPopContainer, FPop>
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure)
	static int32 FindIndex(UPARAM(ref) FPopContainer& Container, UGS_PopData* Object);

	UFUNCTION(BlueprintCallable)
	static void Add(UPARAM(ref) FPopContainer& Container, FPop Element);
	
	UFUNCTION(BlueprintCallable)
	static int32 Subtract(UPARAM(ref) FPopContainer& Container, FPop Element);

	UFUNCTION(BlueprintCallable)
	static void Merge(UPARAM(ref) FPopContainer& Target, UPARAM(ref) FPopContainer& Source);
	
	UFUNCTION(BlueprintPure)
	static FPopContainer Combine(UPARAM(ref) FPopContainer& First, UPARAM(ref) FPopContainer& Second);

	UFUNCTION(BlueprintCallable)
	static void Clear(UPARAM(ref) FPopContainer& Container);

	UFUNCTION(BlueprintPure)
	static FPop Get(UPARAM(ref) FPopContainer& Container, UGS_PopData* Object);

	UFUNCTION(BlueprintPure)
	static FPop Multiply(FPop Struct, float Multiplier);
	
	UFUNCTION(BlueprintPure)
	static FPopContainer MultiplyContainer(UPARAM(ref)FPopContainer& Container, float Multiplier);

	UFUNCTION(BlueprintPure)
	static bool HasType(UPARAM(ref) FPopContainer& Container, UGS_PopData* Type);

	UFUNCTION(BlueprintPure)
	static bool Contains(UPARAM(ref) FPopContainer& Source, UPARAM(ref) FPopContainer& Target);

	UFUNCTION(BlueprintPure)
	static TArray<UGS_PopData*> GetAllTypes(UPARAM(ref) FPopContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static TSet<UGS_PopData*> GetAllTypesSet(UPARAM(ref) FPopContainer& Container);

	UFUNCTION(BlueprintPure)
	static int32 GetTotalSize(UPARAM(ref) FPopContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static FPopContainer Negate(UPARAM(ref) FPopContainer& Container);

	UFUNCTION(BlueprintPure)
	static bool IsEmpty(UPARAM(ref) FPopContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static bool IsNotEmpty(UPARAM(ref) FPopContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static FPopContainer MakeContainer(const FPop& Element);
};
