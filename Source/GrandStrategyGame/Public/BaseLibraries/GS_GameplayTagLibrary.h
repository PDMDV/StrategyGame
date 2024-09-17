#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_GameplayTagLibrary.generated.h"

struct FGameplayTag;
struct FGameplayTagContainer;

UCLASS()
class GRANDSTRATEGYGAME_API UGS_GameplayTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "GameplayTags")
	static FGameplayTagContainer GetAllChildren(FGameplayTag Tag);
	
	UFUNCTION(BlueprintPure, Category = "GameplayTags")
	static FGameplayTagContainer GetAllChildrenWithDepth(FGameplayTag Tag, int32 Depth = 1, bool OnlyExactDepth = true);
	
	UFUNCTION(BlueprintPure, Category = "GameplayTags")
	static FGameplayTag GetDirectParent(FGameplayTag Tag);
	
	UFUNCTION(BlueprintPure, Category = "GameplayTags")
	static int32 GetNumberOfTagNodes(FGameplayTag Tag);
	
	UFUNCTION(BlueprintPure, Category = "GameplayTags")
	static FName GetTagLastName(FGameplayTag Tag);
	
};
