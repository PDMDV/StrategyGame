// Fill out your copyright notice in the Description page of Project Settings.


#include "Province/Data/GS_BuildingData.h"

UGS_BuildingData::UGS_BuildingData()
{
	RequirementsList = CreateDefaultSubobject<URequirementsList>(TEXT("Requirements List"));
}
