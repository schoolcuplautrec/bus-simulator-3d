#include "Maps/ToulouseEnvironment.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AToulouseEnvironment::AToulouseEnvironment()
{
	PrimaryActorTick.bCanEverTick = false;

	// Créer le mesh de la route
	RoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoadMesh"));
	RootComponent = RoadMesh;
}

void AToulouseEnvironment::BeginPlay()
{
	Super::BeginPlay();
	GenerateBuildings();
	GenerateRoads();
	SpawnStreetElements();
}

void AToulouseEnvironment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToulouseEnvironment::GenerateBuildings()
{
	// Générer les bâtiments de manière procédurale
	int32 NumBuildings = (int32)(MapWidth * MapHeight * BuildingDensity / 10000.0f);

	for (int32 i = 0; i < NumBuildings; ++i)
	{
		float RandomX = FMath::RandRange(-MapWidth / 2, MapWidth / 2);
		float RandomY = FMath::RandRange(-MapHeight / 2, MapHeight / 2);
		float RandomScale = FMath::RandRange(200.0f, 800.0f); // Hauteurs variées

		CreateBuildingBlock(FVector(RandomX, RandomY, 0), FVector(RandomScale, 200.0f, RandomScale));
	}
}

void AToulouseEnvironment::GenerateRoads()
{
	// Générer les routes principales
	// Routes principales de Toulouse en grille
}

void AToulouseEnvironment::SpawnStreetElements()
{
	// Générer les éléments de rue
	int32 NumStreetlights = 50;
	int32 NumTrees = 30;

	for (int32 i = 0; i < NumStreetlights; ++i)
	{
		float RandomX = FMath::RandRange(-MapWidth / 2, MapWidth / 2);
		float RandomY = FMath::RandRange(-MapHeight / 2, MapHeight / 2);
		CreateStreetlight(FVector(RandomX, RandomY, 0));
	}

	for (int32 i = 0; i < NumTrees; ++i)
	{
		float RandomX = FMath::RandRange(-MapWidth / 2, MapWidth / 2);
		float RandomY = FMath::RandRange(-MapHeight / 2, MapHeight / 2);
		CreateTree(FVector(RandomX, RandomY, 0));
	}
}

void AToulouseEnvironment::CreateBuildingBlock(FVector Position, FVector Scale)
{
	UStaticMeshComponent* Building = NewObject<UStaticMeshComponent>(this);
	Building->RegisterComponent();
	Building->SetupAttachment(RootComponent);
	Building->SetRelativeLocation(Position);
	Building->SetRelativeScale3D(Scale);

	Buildings.Add(Building);
}

void AToulouseEnvironment::CreateStreetlight(FVector Position)
{
	UStaticMeshComponent* Streetlight = NewObject<UStaticMeshComponent>(this);
	Streetlight->RegisterComponent();
	Streetlight->SetupAttachment(RootComponent);
	Streetlight->SetRelativeLocation(Position + FVector(0, 0, 500));

	Streetlights.Add(Streetlight);
}

void AToulouseEnvironment::CreateTree(FVector Position)
{
	UStaticMeshComponent* Tree = NewObject<UStaticMeshComponent>(this);
	Tree->RegisterComponent();
	Tree->SetupAttachment(RootComponent);
	Tree->SetRelativeLocation(Position);

	Trees.Add(Tree);
}
