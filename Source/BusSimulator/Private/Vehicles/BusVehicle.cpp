#include "Vehicles/BusVehicle.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/DriveSystem.h"
#include "UI/BusHUD.h"

ABusVehicle::ABusVehicle()
{
	PrimaryActorTick.TickInterval = 0.016f; // 60 FPS
	PrimaryActorTick.bCanEverTick = true;

	// Désactiver la collision de pion par défaut
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Créer le mesh du bus
	BusMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BusMesh"));
	RootComponent = BusMesh;

	// Créer le spring arm pour la caméra
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Créer la caméra
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Créer les systèmes
	PhysicsSystem = CreateDefaultSubobject<UPhysicsSystem>(TEXT("PhysicsSystem"));
	DriveSystem = CreateDefaultSubobject<UDriveSystem>(TEXT("DriveSystem"));

	// Initialiser les variables
	CurrentRPM = IdleRPM;
	CurrentGear = 0; // Neutral
	EngineTemperature = 20.0f;
	FuelLevel = 100.0f;
	bIsEngineRunning = false;
	bUseAutomaticTransmission = true;
	bInternalCamera = true;
}

void ABusVehicle::BeginPlay()
{
	Super::BeginPlay();

	// Configurer les références
	if (DriveSystem)
	{
		DriveSystem->StartEngine();
		bIsEngineRunning = true;
	}
}

void ABusVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Mettre à jour les systèmes
	if (DriveSystem && PhysicsSystem && bIsEngineRunning)
	{
		// Appliquer les forces
		PhysicsSystem->ApplyThrottleForce(DriveSystem->GetThrottleInput(), CurrentRPM, CurrentGear, FinalDriveRatio);
		PhysicsSystem->ApplyBrakeForce(DriveSystem->GetBrakeInput(), MaxBrakeTorque);
		PhysicsSystem->ApplySteeringForce(DriveSystem->GetSteeringInput(), MaxSteeringAngle);

		// Mettre à jour la suspension
		PhysicsSystem->UpdateSuspension(DeltaTime);

		// Transmission automatique
		if (bUseAutomaticTransmission)
		{
			DriveSystem->AutomaticGearShift(DeltaTime);
		}

		// Mettre à jour RPM et température
		CurrentRPM = DriveSystem->GetRPM();
		EngineTemperature = DriveSystem->GetEngineTemperature();
		CurrentGear = DriveSystem->GetCurrentGear();
		FuelLevel = FMath::Max(0.0f, FuelLevel - (DriveSystem->GetFuelConsumption() * DeltaTime));
	}
}

void ABusVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Configuration d'input standards Unreal
	if (PlayerInputComponent)
	{
		// À implémenter avec Enhanced Input System
	}
}

float ABusVehicle::GetCurrentRPM() const
{
	return DriveSystem ? DriveSystem->GetRPM() : 0.0f;
}

float ABusVehicle::GetCurrentSpeed() const
{
	return PhysicsSystem ? PhysicsSystem->GetSpeed() : 0.0f;
}

int32 ABusVehicle::GetCurrentGear() const
{
	return DriveSystem ? DriveSystem->GetCurrentGear() : 0;
}

float ABusVehicle::GetEngineTemperature() const
{
	return DriveSystem ? DriveSystem->GetEngineTemperature() : 0.0f;
}

float ABusVehicle::GetFuelLevel() const
{
	return FuelLevel;
}
