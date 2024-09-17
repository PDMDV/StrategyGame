#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_ContainerTemplate.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_ArmyUnitLibrary.generated.h"

class UGS_UnitData;

USTRUCT(BlueprintType)
struct FArmyUnit
{
	GENERATED_BODY()

	FArmyUnit() {};
	FArmyUnit(UGS_UnitData* UnitData) : Type(UnitData){};
	FArmyUnit(UGS_UnitData* UnitData, int32 Amount) : Type(UnitData), Amount(Amount){};

	friend bool operator==(const FArmyUnit& Lhs, const FArmyUnit& RHS)
	{
		return Lhs.Type == RHS.Type;
	}

	friend bool operator!=(const FArmyUnit& Lhs, const FArmyUnit& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGS_UnitData* Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 0;
};

USTRUCT(BlueprintType)
struct FArmyUnitsContainer
{
	GENERATED_BODY()

	TArray<FArmyUnit>& GetArray(){ return Units;}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FArmyUnit> Units;
}; 

UCLASS()
class GRANDSTRATEGYGAME_API UGS_ArmyUnitLibrary : public UBlueprintFunctionLibrary, public TContainerFunctions<FArmyUnitsContainer, FArmyUnit>
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintPure)
	static int32 FindIndex(UPARAM(ref) FArmyUnitsContainer& Container, UGS_UnitData* Object);

	UFUNCTION(BlueprintCallable)
	static void Add(UPARAM(ref) FArmyUnitsContainer& Container, FArmyUnit Element);

	UFUNCTION(BlueprintCallable)
	static int32 Subtract(UPARAM(ref) FArmyUnitsContainer& Container, FArmyUnit Element);

	UFUNCTION(BlueprintCallable)
	static void Merge(UPARAM(ref) FArmyUnitsContainer& Target, UPARAM(ref) FArmyUnitsContainer& Source);

	UFUNCTION(BlueprintPure)
	static FArmyUnitsContainer Combine(UPARAM(ref) FArmyUnitsContainer& First, UPARAM(ref) FArmyUnitsContainer& Second);

	UFUNCTION(BlueprintCallable)
	static void Clear(UPARAM(ref) FArmyUnitsContainer& Container);

	UFUNCTION(BlueprintPure)
	static FArmyUnit Get(UPARAM(ref) FArmyUnitsContainer& Container, UGS_UnitData* Object);

	UFUNCTION(BlueprintPure)
	static FArmyUnit Multiply(FArmyUnit Struct, float Multiplier);
	
	UFUNCTION(BlueprintPure)
	static FArmyUnitsContainer MultiplyContainer(UPARAM(ref)FArmyUnitsContainer& Container, float Multiplier);

	UFUNCTION(BlueprintPure)
	static bool HasType(UPARAM(ref) FArmyUnitsContainer& Container, UGS_UnitData* Type);

	UFUNCTION(BlueprintPure)
	static bool Contains(UPARAM(ref) FArmyUnitsContainer& Source, UPARAM(ref) FArmyUnitsContainer& Target);

	UFUNCTION(BlueprintPure)
	static TArray<UGS_UnitData*> GetAllTypes(UPARAM(ref) FArmyUnitsContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static TSet<UGS_UnitData*> GetAllTypesSet(UPARAM(ref) FArmyUnitsContainer& Container);

	UFUNCTION(BlueprintPure)
	static int32 GetTotalSize(UPARAM(ref) FArmyUnitsContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static FArmyUnitsContainer Negate(UPARAM(ref) FArmyUnitsContainer& Container);

	UFUNCTION(BlueprintPure)
	static bool IsEmpty(UPARAM(ref) FArmyUnitsContainer& Container);

	UFUNCTION(BlueprintPure)
	static bool IsNotEmpty(UPARAM(ref) FArmyUnitsContainer& Container);
	
	UFUNCTION(BlueprintPure)
	static FArmyUnitsContainer MakeContainer(const FArmyUnit& Element);
	
};
