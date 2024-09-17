#pragma once

#include "CoreMinimal.h"
#include "GS_Trigger.generated.h"

class UGS_ActionInfo;

UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories)
class GRANDSTRATEGYGAME_API UGS_Trigger : public UObject
{
	GENERATED_BODY()
	
public:
	
	UGS_Trigger();
	
	// Required by BlueprintLibraries
	UWorld* GetWorld() const override;

	void Start(UWorld* World);

	UFUNCTION(BlueprintNativeEvent)
	void BeginPlay();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Register(UObject* Object);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Triggered(UObject* Owner, UObject* Triggerer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, SimpleDisplay, meta = (DisplayName = "Actions", DisplayPriority = 0))
	TArray<TObjectPtr<UGS_ActionInfo>> Actions;

	UPROPERTY(BlueprintReadWrite)
	bool Initialized;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<UObject>> RegisteredList;
};
