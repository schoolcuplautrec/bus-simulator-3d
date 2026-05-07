#include "Systems/PhysicsSystem.h"
#include "Vehicles/BusVehicle.h"
#include "GameFramework/Character.h"

UPhysicsSystem::UPhysicsSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentVelocity = FVector::ZeroVector;
	CurrentAcceleration = FVector::ZeroVector;
	CurrentSteeringAngle = 0.0f;
	LongitudinalSlip = 0.0f;
	LateralSlip = 0.0f;
	TireTemperature = 20.0f;

	// Initialiser les positions des roues (pour un bus standard)
	WheelPositions = {
		FVector(200, -100, 0),   // Avant gauche
		FVector(200, 100, 0),    // Avant droit
		FVector(-200, -100, 0),  // Arrière gauche
		FVector(-200, 100, 0),   // Arrière droit
	};

	WheelCompressions.SetNum(4, false);
}

void UPhysicsSystem::BeginPlay()
{
	Super::BeginPlay();
	BusOwner = Cast<ABusVehicle>(GetOwner());
}

void UPhysicsSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!BusOwner) return;

	UpdateDrag(DeltaTime);
	UpdateRollingResistance();
	UpdateWheelPhysics(DeltaTime);

	// Appliquer l'accélération
	CurrentVelocity += CurrentAcceleration * DeltaTime;

	// Limiter la vitesse maximale
	const float MaxSpeed = 2500.0f; // cm/s = 90 km/h
	if (CurrentVelocity.Length() > MaxSpeed)
	{
		CurrentVelocity = CurrentVelocity.GetSafeNormal() * MaxSpeed;
	}

	// Mettre à jour la position du bus
	FVector NewLocation = BusOwner->GetActorLocation() + CurrentVelocity * DeltaTime;
	BusOwner->SetActorLocation(NewLocation);
}

void UPhysicsSystem::ApplyThrottleForce(float ThrottleInput, float CurrentRPM, int32 CurrentGear, float FinalDriveRatio)
{
	if (!BusOwner || CurrentGear == 0) return;

	// Obtenir le rapport d'engrenage
	float GearRatio = 0.0f;
	switch (CurrentGear)
	{
		case 1: GearRatio = BusOwner->GearRatio1; break;
		case 2: GearRatio = BusOwner->GearRatio2; break;
		case 3: GearRatio = BusOwner->GearRatio3; break;
		case 4: GearRatio = BusOwner->GearRatio4; break;
		case 5: GearRatio = BusOwner->GearRatio5; break;
		case -1: GearRatio = BusOwner->GearRatioReverse; break;
	}

	// Calculer la puissance du moteur (Watts)
	float RPMRatio = CurrentRPM / BusOwner->MaxRPM;
	float EnginePower = BusOwner->MaxEnginePower * ThrottleInput * (1.0f - (RPMRatio * RPMRatio * 0.5f));

	// Calculer le couple
	float EngineTorque = EnginePower / (CurrentRPM > 1.0f ? CurrentRPM : 1.0f);

	// Calculer le couple aux roues
	float WheelTorque = EngineTorque * GearRatio * FinalDriveRatio * CalculateTireGrip(LongitudinalSlip);

	// Calculer la force longitudinale
	float LongitudinalForce = WheelTorque * 4.0f / (WheelRadius * 0.01f); // 4 roues

	// Appliquer la force
	CurrentAcceleration.X = LongitudinalForce / BusMass;
}

void UPhysicsSystem::ApplyBrakeForce(float BrakeInput, float MaxBrakeTorque)
{
	if (!BusOwner) return;

	float BrakeTorque = MaxBrakeTorque * BrakeInput;
	float BrakeForce = BrakeTorque * 4.0f / (WheelRadius * 0.01f); // 4 roues

	CurrentAcceleration.X -= (BrakeForce / BusMass) * (BrakeTorque > 0 ? 1.0f : 0.0f);
}

void UPhysicsSystem::ApplySteeringForce(float SteeringInput, float MaxSteeringAngle)
{
	CurrentSteeringAngle = FMath::Lerp(CurrentSteeringAngle, SteeringInput * MaxSteeringAngle, 0.1f);

	// Appliquer la direction via rotation
	if (BusOwner && GetWorld())
	{
		FRotator NewRotation = BusOwner->GetActorRotation();
		NewRotation.Yaw += CurrentSteeringAngle * 0.01f;
		BusOwner->SetActorRotation(NewRotation);
	}
}

void UPhysicsSystem::UpdateSuspension(float DeltaTime)
{
	// Appliquer la suspension pour chaque roue
	for (int32 i = 0; i < 4; ++i)
	{
		FVector WheelWorldPos = BusOwner->GetActorLocation() + BusOwner->GetActorRotation().RotateVector(WheelPositions[i]);

		// Raycasting pour détecter le sol
		FHitResult HitResult;
		FVector TraceEnd = WheelWorldPos - FVector(0, 0, 300.0f);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(BusOwner);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, WheelWorldPos, TraceEnd, ECC_WorldStatic, QueryParams))
		{
			float CompressionAmount = (WheelPositions[i].Z - HitResult.Distance);
			WheelCompressions[i] = FMath::Max(0.0f, CompressionAmount);

			// Force de suspension
			float SuspensionForce = WheelCompressions[i] * GetWorld()->GetGravityZ() * BusMass / 4.0f;
			CurrentAcceleration.Z += SuspensionForce / BusMass;
		}
	}
}

void UPhysicsSystem::UpdateDrag(float DeltaTime)
{
	// Résistance aérodynamique (F = 0.5 * rho * Cd * A * v²)
	float Speed = CurrentVelocity.Length();
	float DragForce = 0.5f * 1.225f * AirResistanceFactor * 8.0f * (Speed * Speed);
	CurrentAcceleration.X -= (DragForce / BusMass) * (CurrentVelocity.X > 0 ? 1.0f : -1.0f);
}

void UPhysicsSystem::UpdateRollingResistance()
{
	// Résistance de roulement
	float RollingForce = BusMass * GetWorld()->GetGravityZ() * RollingResistanceFactor;
	float Speed = CurrentVelocity.Length();
	if (Speed > 0)
	{
		CurrentAcceleration.X -= (RollingForce / BusMass) * (CurrentVelocity.X > 0 ? 1.0f : -1.0f);
	}
}

float UPhysicsSystem::CalculateTireGrip(float Slip)
{
	// Modèle simplifié de courbe d'adhérence des pneus (Pacejka)
	const float PeakSlip = 0.1f;
	const float StiffnessFactor = 1.0f;

	if (FMath::Abs(Slip) < PeakSlip)
	{
		return 1.0f - (FMath::Abs(Slip) / PeakSlip) * 0.3f;
	}
	else
	{
		return 0.7f * (1.0f - (FMath::Abs(Slip) - PeakSlip) * 0.5f);
	}
}

void UPhysicsSystem::UpdateWheelPhysics(float DeltaTime)
{
	// Calculer le glissement longitudinal
	float Speed = CurrentVelocity.Length();
	if (Speed > 1.0f)
	{
		// Simplification : calcul du glissement en fonction de l'accélération
		LongitudinalSlip = FMath::Clamp(CurrentAcceleration.X / (BusMass * 10.0f), -1.0f, 1.0f);
	}

	// Température des pneus
	TireTemperature = FMath::Lerp(TireTemperature, 20.0f + (FMath::Abs(LongitudinalSlip) * 50.0f), DeltaTime * 0.1f);
}
