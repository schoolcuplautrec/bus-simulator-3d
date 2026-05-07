#include "Vehicles/BusArticulatedBP.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

ABusArticulatedBP::ABusArticulatedBP()
{
	PrimaryActorTick.bCanEverTick = true;

	// Créer le corps principal du bus
	MainBusBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainBusBody"));
	RootComponent = MainBusBody;

	// Créer la remorque
	TrailerBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TrailerBody"));
	TrailerBody->SetupAttachment(RootComponent);
}

void ABusArticulatedBP::BeginPlay()
{
	Super::BeginPlay();
	SetupMainBus();
	SetupTrailer();
	SetupArticulation();
}

void ABusArticulatedBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABusArticulatedBP::SetupMainBus()
{
	// Configuration de la section principale du bus
	// Les meshes réels seraient importés depuis des assets
}

void ABusArticulatedBP::SetupTrailer()
{
	// Configuration de la remorque
	TrailerBody->SetRelativeLocation(FVector(-600, 0, 0));
}

void ABusArticulatedBP::SetupArticulation()
{
	// Point d'articulation entre le bus et la remorque
	// Permettrait une flexibilité lors des virages
}
