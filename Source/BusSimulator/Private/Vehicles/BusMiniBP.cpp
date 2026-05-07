#include "Vehicles/BusMiniBP.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

ABusMiniBP::ABusMiniBP()
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

	RearDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearDoor"));
	RearDoor->SetupAttachment(RootComponent);
}

void ABusMiniBP::BeginPlay()
{
	Super::BeginPlay();
	SetupMeshes();
	SetupMaterials();
}

void ABusMiniBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABusMiniBP::SetupMeshes()
{
	// Positionner les roues pour un mini-bus
	FrontWheel_Left->SetRelativeLocation(FVector(150, -120, -40));
	FrontWheel_Right->SetRelativeLocation(FVector(150, 120, -40));
	RearWheel_Left->SetRelativeLocation(FVector(-250, -120, -40));
	RearWheel_Right->SetRelativeLocation(FVector(-250, 120, -40));
}

void ABusMiniBP::SetupMaterials()
{
	// Configuration des matériaux pour le mini-bus
}
