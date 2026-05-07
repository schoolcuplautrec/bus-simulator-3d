#include "Vehicles/BusStandardBP.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ABusStandardBP::ABusStandardBP()
{
	PrimaryActorTick.bCanEverTick = true;

	// Créer la carrosserie
	BusBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BusBody"));
	RootComponent = BusBody;

	// Créer les roues
	FrontWheel_Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheel_Left"));
	FrontWheel_Left->SetupAttachment(RootComponent);

	FrontWheel_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheel_Right"));
	FrontWheel_Right->SetupAttachment(RootComponent);

	RearWheel_Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheel_Left"));
	RearWheel_Left->SetupAttachment(RootComponent);

	RearWheel_Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheel_Right"));
	RearWheel_Right->SetupAttachment(RootComponent);

	// Créer les portes
	FrontDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontDoor"));
	FrontDoor->SetupAttachment(RootComponent);

	MiddleDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MiddleDoor"));
	MiddleDoor->SetupAttachment(RootComponent);

	RearDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearDoor"));
	RearDoor->SetupAttachment(RootComponent);
}

void ABusStandardBP::BeginPlay()
{
	Super::BeginPlay();
	SetupMeshes();
	SetupMaterials();
	SetupDoors();
	SetupWindows();
}

void ABusStandardBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABusStandardBP::SetupMeshes()
{
	// Ces données seraient remplies par des meshes réels dans l'éditeur
	// Positionner les roues
	FrontWheel_Left->SetRelativeLocation(FVector(200, -150, -50));
	FrontWheel_Right->SetRelativeLocation(FVector(200, 150, -50));
	RearWheel_Left->SetRelativeLocation(FVector(-400, -150, -50));
	RearWheel_Right->SetRelativeLocation(FVector(-400, 150, -50));
}

void ABusStandardBP::SetupMaterials()
{
	// Créer des instances de matériaux dynamiques
	if (BusBody)
	{
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BusBody->GetMaterial(0), this);
		BusBody->SetMaterial(0, DynMaterial);
	}
}

void ABusStandardBP::SetupDoors()
{
	// Positionner les portes
	FrontDoor->SetRelativeLocation(FVector(100, 0, 100));
	MiddleDoor->SetRelativeLocation(FVector(-100, 0, 100));
	RearDoor->SetRelativeLocation(FVector(-300, 0, 100));
}

void ABusStandardBP::SetupWindows()
{
	// Les fenêtres seraient gérées par blueprint
}
