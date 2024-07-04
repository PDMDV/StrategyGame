// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_PopLibrary.generated.h"

class UGS_PopData;

USTRUCT(BlueprintType)
struct FPop
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGS_PopData> PopData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Size;
};

UCLASS()
class GRANDSTRATEGYGAME_API UGS_PopLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
