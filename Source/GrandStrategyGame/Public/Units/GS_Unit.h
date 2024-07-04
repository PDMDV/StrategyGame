#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Map/MapObject.h"
#include "GS_Unit.generated.h"

class UAbilitySystemComponent;

UCLASS()
class GRANDSTRATEGYGAME_API AGS_Unit : public AMapObject, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	AGS_Unit();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
