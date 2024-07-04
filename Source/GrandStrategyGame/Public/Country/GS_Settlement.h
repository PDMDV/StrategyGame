
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Map/MapObject.h"
#include "GS_Settlement.generated.h"

class UAbilitySystemComponent;
class USettlementAttributeSet;

UCLASS()
class GRANDSTRATEGYGAME_API AGS_Settlement : public AMapObject, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	AGS_Settlement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USettlementAttributeSet> AttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void BeginPlay() override;

};
