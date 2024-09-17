#include "Buildings/GS_Building.h"

UGS_Building* UGS_Building::CreateBuilding(UGS_BuildingData* BuildingType, int32 Level, int32 Mark, UObject* Outer, TSubclassOf<UGS_Building> Class)
{
	UGS_Building* Building = NewObject<UGS_Building>(Outer, Class);
	Building->BuildingData = BuildingType;
	Building->Level = Level;
	Building->Mark = Mark;
	return Building;
}

void UGS_Building::ChangeLevelBy(int32 Value)
{
	Level += Value;
	Level = FMath::Max(0, Level);
}
