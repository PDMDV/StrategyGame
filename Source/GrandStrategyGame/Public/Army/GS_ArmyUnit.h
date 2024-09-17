#pragma once

#include "CoreMinimal.h"
#include "BaseData/GS_Object.h"
#include "GS_ArmyUnit.generated.h"

class UGS_UnitData;
class AGS_Settlement;

UCLASS(Blueprintable, BlueprintType)
class GRANDSTRATEGYGAME_API UGS_ArmyUnit : public UGS_Object
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	UGS_UnitData* Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	AGS_Settlement* Settlement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	int32 CurrentAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	int32 MaxAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	float Organization = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	float Supply = 0.0;
};
