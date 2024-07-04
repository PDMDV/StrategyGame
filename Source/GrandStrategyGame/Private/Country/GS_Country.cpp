// Fill out your copyright notice in the Description page of Project Settings.


#include "Country\GS_Country.h"

#include "AbilitySystemComponent.h"
#include "Line\GS_LineComponent.h"

// Sets default values
AGS_Country::AGS_Country()
{
	RootScene = CreateDefaultSubobject<ULineComponent>(TEXT("Root Scene"));
	SetRootComponent(RootScene);
	
	Borders = CreateDefaultSubobject<ULineComponent>(TEXT("Borders"));
	Borders->SetupAttachment(GetRootComponent());
	Borders->SetAbsolute(true,true,true);
	
	AbilitySystemComponent  = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability Sytem Component"));
}

// Called when the game starts or when spawned
void AGS_Country::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGS_Country::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

