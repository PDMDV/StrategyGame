#pragma once

#include "CoreMinimal.h"
#include "GS_Order.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOrderFinished, UGS_Order*, Order);

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_Order : public UObject
{
	GENERATED_BODY()

public:

	// Required by BlueprintLibraries
	UWorld* GetWorld() const override;

	UPROPERTY(BlueprintAssignable)
	FOrderFinished OnOrderFinished;

	UFUNCTION(BlueprintCallable)
	void Finish();

	UFUNCTION(BlueprintCallable)
	bool TryExecute(UObject* Target);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Execute(UObject* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool CanBeExecuted(UObject* Target);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Cancel(UObject* Target);
	
};
