#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_Object.h"
#include "GS_ActionInstance.generated.h"

class UGS_EffectInstance;
class UGS_ActionInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionFinished, UGS_ActionInstance*, ActionInstance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActionCanceled, UGS_ActionInstance*, ActionInstance);

UCLASS(Blueprintable)
class GRANDSTRATEGYGAME_API UGS_ActionInstance : public UGS_Object
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Init();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Perform();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void End();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Cancel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsCapable();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
    float GetProgress();
	
	UPROPERTY(BlueprintAssignable)
	FActionFinished OnActionFinished;

	UPROPERTY(BlueprintAssignable)
	FActionCanceled OnActionCanceled;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGS_ActionInfo> ActionInfo;
	
	UPROPERTY(BlueprintReadOnly)
	UObject* Source;

	UPROPERTY(BlueprintReadOnly)
	UObject* Target;

	UPROPERTY()
	TArray<UGS_EffectInstance*> EffectInstances;
};
