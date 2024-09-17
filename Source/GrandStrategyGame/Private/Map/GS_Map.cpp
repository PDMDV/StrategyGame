#include "Map\GS_Map.h"

#include "Line\GS_LineComponent.h"
#include "PCGComponent.h"

AGS_Map::AGS_Map()
{
	MapMesh = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("MapMesh"));
	SetRootComponent(MapMesh);
	
	CellsBorders = CreateDefaultSubobject<ULineComponent>(TEXT("Test"));
    CellsBorders->SetupAttachment(GetRootComponent());

	RegionsBorders = CreateDefaultSubobject<ULineComponent>(TEXT("Regions Borders"));
	RegionsBorders->SetupAttachment(GetRootComponent());
	
	RiverSystem = CreateDefaultSubobject<ULineComponent>(TEXT("RiverSystem"));
	RiverSystem->SetupAttachment(GetRootComponent()); 

	PCG = CreateDefaultSubobject<UPCGComponent>(TEXT("PCG"));
#if WITH_EDITOR
	PCG->OnPCGGraphCleanedDelegate.AddUObject(this, &AGS_Map::OnPCGCleanup);
#endif
}

float AGS_Map::GetHeightAtLocation(FVector2D Location, FVector& Normal)
{
	FHitResult OutHit;
	const FVector Start = {Location.X, Location.Y, 10000.f};
	const FVector End = {Location.X, Location.Y, -10000.f};
	FCollisionQueryParams Params;
	MapMesh->LineTraceComponent(OutHit, Start, End, Params);
	Normal = OutHit.Normal;
	return OutHit.Location.Z;
}

void AGS_Map::BeginPlay()
{
	Super::BeginPlay();
}

void AGS_Map::OnPCGCleanup(UPCGComponent* InPCG)
{
	RiverSystem->Reset();
}

void AGS_Map::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

