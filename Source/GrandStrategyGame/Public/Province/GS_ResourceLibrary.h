// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GS_ResourceLibrary.generated.h"


class UGS_ResourceData;

USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()

	FResource() {};
	FResource(const TObjectPtr<UGS_ResourceData>& ResourceData): ResourceData(ResourceData), Amount(0){};

	friend bool operator==(const FResource& Lhs, const FResource& RHS)
	{
		return Lhs.ResourceData == RHS.ResourceData;
	}

	friend bool operator!=(const FResource& Lhs, const FResource& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGS_ResourceData> ResourceData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount;
};

UCLASS(Blueprintable)
class GRANDSTRATEGYGAME_API UGS_ResourceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
