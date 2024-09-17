
#include "Province/GS_ProvinceLibrary.h"

void UGS_ProvinceLibrary::AddTag(FProvince& Province, const FGameplayTag& TagToAdd)
{
	Province.Tags.AddTag(TagToAdd);
}

bool UGS_ProvinceLibrary::RemoveTag(FProvince& Province, const FGameplayTag& TagToRemove)
{
	return Province.Tags.RemoveTag(TagToRemove);
}
