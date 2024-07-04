
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GS_ProvincesManager.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRANDSTRATEGYGAME_API UGS_ProvincesManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGS_ProvincesManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
