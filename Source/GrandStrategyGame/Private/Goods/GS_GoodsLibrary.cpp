// Fill out your copyright notice in the Description page of Project Settings.


#include "Goods/GS_GoodsLibrary.h"
#include "BaseData/GS_ContainerTemplate.h"

int32 UGS_GoodsLibrary::FindIndex(FGoodsContainer& Container, UGS_GoodData* Object)
{
	return FindIndexT(Container, Object);
}

void UGS_GoodsLibrary::Add(FGoodsContainer& Container, FGoods Element)
{
	AddT(Container, Element);
}

float UGS_GoodsLibrary::Subtract(FGoodsContainer& Container, FGoods Element)
{
	return SubtractT(Container, Element);
}

void UGS_GoodsLibrary::Merge(FGoodsContainer& Target, FGoodsContainer& Source)
{
	MergeT(Target, Source);
}

FGoodsContainer UGS_GoodsLibrary::Combine(FGoodsContainer& First, FGoodsContainer& Second)
{
	return CombineT(First, Second);
}

void UGS_GoodsLibrary::Clear(FGoodsContainer& Container)
{
	ClearT(Container);
}

FGoods UGS_GoodsLibrary::Get(FGoodsContainer& Container, UGS_GoodData* Type)
{
	return GetT(Container, Type);
}

FGoods UGS_GoodsLibrary::Multiply(FGoods Struct, float Multiplier)
{
	return MultiplyT(Struct, Multiplier);
}

FGoodsContainer UGS_GoodsLibrary::MultiplyContainer(FGoodsContainer& Container, float Multiplier)
{
	return MultiplyContainerT(Container, Multiplier);
}

bool UGS_GoodsLibrary::HasType(FGoodsContainer& Container, UGS_GoodData* Type)
{
	return HasTypeT(Container, Type);
}

bool UGS_GoodsLibrary::Contains(FGoodsContainer& Source, FGoodsContainer& Target)
{
	return ContainsT(Source, Target);
}

TArray<UGS_GoodData*> UGS_GoodsLibrary::GetAllTypes(FGoodsContainer& Container)
{
	return GetAllTypesT(Container);
}

TSet<UGS_GoodData*> UGS_GoodsLibrary::GetAllTypesSet(FGoodsContainer& Container)
{
	return GetAllTypesSetT(Container);
}

float UGS_GoodsLibrary::GetTotalSize(FGoodsContainer& Container)
{
	return GetTotalSizeT(Container);
}

FGoodsContainer UGS_GoodsLibrary::Negate(FGoodsContainer& Container)
{
	return NegateT(Container);
}

bool UGS_GoodsLibrary::IsEmpty(FGoodsContainer& Container)
{
	return IsEmptyT(Container);
}

bool UGS_GoodsLibrary::IsNotEmpty(FGoodsContainer& Container)
{
	return IsNotEmptyT(Container);
}

FGoodsContainer UGS_GoodsLibrary::MakeContainer(const FGoods& Element)
{
	return MakeContainerT(Element);
}
