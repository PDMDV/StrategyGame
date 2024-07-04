// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProvinceChanged, int32, OldProvince, int32, NewProvice);

UENUM(BlueprintType)
enum class EVisibilityType : uint8 {
     AlwaysVisible		UMETA(DisplayName = "Always Visible"),
     Fogged				UMETA(DisplayName = "Fogged"),
     AlwaysInvisible    UMETA(DisplayName = "Always Invisible"),
};

UCLASS()
class GRANDSTRATEGYGAME_API AMapObject : public AActor
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnProvinceChanged OnProvinceChanged;
	
public:	
	AMapObject();

protected:
	virtual void BeginPlay() override;

	void AnnounceProvinceChange();

public:	
	virtual void Tick(float DeltaTime) override;
 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Events")
	void ProvinceChanged(int32 OldProvince, int32 NewProvince);

	UFUNCTION(BlueprintCallable)
	void ChangeProvince(int32 NewProvinceID);

	UFUNCTION(BlueprintCallable)
	void SetFogged(bool IsFogged);
	void InitVisibility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	int32 ProvinceID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	EVisibilityType VisibilityType = EVisibilityType::Fogged;
};
