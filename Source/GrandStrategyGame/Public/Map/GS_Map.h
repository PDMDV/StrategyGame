// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Province/GS_ProvinceLibrary.h"
#include "GameFramework/Actor.h"
#include "GS_Map.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
class UPCGComponent;
class UDynamicMeshComponent;
class ULineComponent;

UCLASS()
class GRANDSTRATEGYGAME_API AGS_Map : public AActor
{
	GENERATED_BODY()
	
public:	
	AGS_Map();

	UFUNCTION(BlueprintPure)
	float GetHeightAtLocation(FVector2D Location, FVector& Normal);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UDynamicMeshComponent> MapMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ULineComponent> CellsBorders;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ULineComponent> RegionsBorders;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<ULineComponent> RiverSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UPCGComponent> PCG;
	
	virtual void BeginPlay() override;

	void OnPCGCleanup(UPCGComponent* InPCG);

public:	
	virtual void Tick(float DeltaTime) override;

};
