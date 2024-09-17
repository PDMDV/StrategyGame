
#include "Province/GS_PopLibrary.h"
#include "Province/Data/GS_PopData.h"
#include "BaseData/GS_ContainerTemplate.h"

int32 UGS_PopLibrary::FindIndex(FPopContainer& Container, UGS_PopData* Object)
{
	return FindIndexT(Container, Object);
}

void UGS_PopLibrary::Add(FPopContainer& Container, FPop Element)
{
	AddT(Container, Element);
}

int32 UGS_PopLibrary::Subtract(FPopContainer& Container, FPop Element)
{
	return SubtractT(Container, Element);
}

void UGS_PopLibrary::Merge(FPopContainer& Target, FPopContainer& Source)
{
	MergeT(Target, Source);
}

FPopContainer UGS_PopLibrary::Combine(FPopContainer& First, FPopContainer& Second)
{
	return CombineT(First, Second);
}

void UGS_PopLibrary::Clear(FPopContainer& Container)
{
	ClearT(Container);
}

FPop UGS_PopLibrary::Get(FPopContainer& Container, UGS_PopData* Object)
{
	return GetT(Container, Object);
}

FPop UGS_PopLibrary::Multiply(FPop Struct, float Multiplier)
{
	return MultiplyT(Struct, Multiplier);
}

FPopContainer UGS_PopLibrary::MultiplyContainer(FPopContainer& Container, float Multiplier)
{
	return MultiplyContainerT(Container, Multiplier);
}

bool UGS_PopLibrary::HasType(FPopContainer& Container, UGS_PopData* Type)
{
	return HasTypeT(Container, Type);
}

bool UGS_PopLibrary::Contains(FPopContainer& Source, FPopContainer& Target)
{
	return ContainsT(Source, Target);
}

TArray<UGS_PopData*> UGS_PopLibrary::GetAllTypes(FPopContainer& Container)
{
	return GetAllTypesT(Container);
}

TSet<UGS_PopData*> UGS_PopLibrary::GetAllTypesSet(FPopContainer& Container)
{
	return GetAllTypesSetT(Container);
}

int32 UGS_PopLibrary::GetTotalSize(FPopContainer& Container)
{
	return GetTotalSizeT(Container);
}

FPopContainer UGS_PopLibrary::Negate(FPopContainer& Container)
{
	return NegateT(Container);
}

bool UGS_PopLibrary::IsEmpty(FPopContainer& Container)
{
	return IsEmptyT(Container);
}

bool UGS_PopLibrary::IsNotEmpty(FPopContainer& Container)
{
	return IsNotEmptyT(Container);
}

FPopContainer UGS_PopLibrary::MakeContainer(const FPop& Element)
{
	return MakeContainerT(Element);
}
