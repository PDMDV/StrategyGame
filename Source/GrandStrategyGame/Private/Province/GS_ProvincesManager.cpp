// Fill out your copyright notice in the Description page of Project Settings.


#include "Province/GS_ProvincesManager.h"

UGS_ProvincesManager::UGS_ProvincesManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGS_ProvincesManager::BeginPlay()
{
	Super::BeginPlay();
}

void UGS_ProvincesManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

