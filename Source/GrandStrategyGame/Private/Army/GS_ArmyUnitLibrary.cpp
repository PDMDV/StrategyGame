// Fill out your copyright notice in the Description page of Project Settings.


#include "Army/GS_ArmyUnitLibrary.h"

#include "Army/GS_UnitData.h"
#include "BaseData/GS_ContainerTemplate.h"

int32 UGS_ArmyUnitLibrary::FindIndex(FArmyUnitsContainer& Container, UGS_UnitData* Object)
{
	return FindIndexT(Container, Object);
}

void UGS_ArmyUnitLibrary::Add(FArmyUnitsContainer& Container, FArmyUnit Element)
{
	AddT(Container, Element);
}

int32 UGS_ArmyUnitLibrary::Subtract(FArmyUnitsContainer& Container, FArmyUnit Element)
{
	return SubtractT(Container, Element);
}

void UGS_ArmyUnitLibrary::Merge(FArmyUnitsContainer& Target, FArmyUnitsContainer& Source)
{
	MergeT(Target, Source);
}

FArmyUnitsContainer UGS_ArmyUnitLibrary::Combine(FArmyUnitsContainer& First, FArmyUnitsContainer& Second)
{
	return CombineT(First, Second);
}

void UGS_ArmyUnitLibrary::Clear(FArmyUnitsContainer& Container)
{
	ClearT(Container);
}

FArmyUnit UGS_ArmyUnitLibrary::Get(FArmyUnitsContainer& Container, UGS_UnitData* Object)
{
	return GetT(Container, Object);
}

FArmyUnit UGS_ArmyUnitLibrary::Multiply(FArmyUnit Struct, float Multiplier)
{
	return MultiplyT(Struct, Multiplier);
}

FArmyUnitsContainer UGS_ArmyUnitLibrary::MultiplyContainer(FArmyUnitsContainer& Container, float Multiplier)
{
	return MultiplyContainerT(Container, Multiplier);
}

bool UGS_ArmyUnitLibrary::HasType(FArmyUnitsContainer& Container, UGS_UnitData* Type)
{
	return HasTypeT(Container, Type);
}

bool UGS_ArmyUnitLibrary::Contains(FArmyUnitsContainer& Source, FArmyUnitsContainer& Target)
{
	return ContainsT(Source, Target);
}

TArray<UGS_UnitData*> UGS_ArmyUnitLibrary::GetAllTypes(FArmyUnitsContainer& Container)
{
	return GetAllTypesT(Container);
}

TSet<UGS_UnitData*> UGS_ArmyUnitLibrary::GetAllTypesSet(FArmyUnitsContainer& Container)
{
	return GetAllTypesSetT(Container);
}

int32 UGS_ArmyUnitLibrary::GetTotalSize(FArmyUnitsContainer& Container)
{
	return GetTotalSizeT(Container);
}

FArmyUnitsContainer UGS_ArmyUnitLibrary::Negate(FArmyUnitsContainer& Container)
{
	return NegateT(Container);
}

bool UGS_ArmyUnitLibrary::IsEmpty(FArmyUnitsContainer& Container)
{
	return IsEmptyT(Container);
}

bool UGS_ArmyUnitLibrary::IsNotEmpty(FArmyUnitsContainer& Container)
{
	return IsNotEmptyT(Container);
}

FArmyUnitsContainer UGS_ArmyUnitLibrary::MakeContainer(const FArmyUnit& Element)
{
	return MakeContainerT(Element);
}
