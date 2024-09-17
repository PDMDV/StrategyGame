#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_Object.h"
#include "GS_EffectInstance.generated.h"

class UGS_EffectInfo;

UCLASS(Blueprintable)
class GRANDSTRATEGYGAME_API UGS_EffectInstance : public UGS_Object
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsCapable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Apply();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Refresh();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool End();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Invert();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Init();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UGS_EffectInfo> EffectInfo;
	
	UPROPERTY(BlueprintReadOnly)
	UObject* Source;

	UPROPERTY(BlueprintReadOnly)
	UObject* Target;
};
