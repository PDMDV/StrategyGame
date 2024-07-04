#pragma once

#include "CoreMinimal.h"
#include "GS_Effect.generated.h"

class UGameplayEffect;

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_Effect : public UObject
{
	GENERATED_BODY()
public:
	// Required by BlueprintLibraries
	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsCapable(UObject* Source, UObject* Target);

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffects(UObject* Source, UObject* Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Apply(UObject* Source, UObject* Target);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<const TSubclassOf<UGameplayEffect>> Effects;
	
};
