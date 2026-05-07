#include "Systems/DriveSystem.h"
#include "Vehicles/BusVehicle.h"

UDriveSystem::UDriveSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	ThrottleInput = 0.0f;
	BrakeInput = 0.0f;
	SteeringInput = 0.0f;
	CurrentRPM = IdleRPM;
	CurrentGear = 0; // Neutral
	bEngineRunning = false;
	EngineTemperature = 20.0f;
	FuelConsumption = 0.0f;
	GearShiftCooldown = 0.2f;
	LastGearShiftTime = 0.0f;
}

void UDriveSystem::BeginPlay()
{
	Super::BeginPlay();
	BusOwner = Cast<ABusVehicle>(GetOwner());
}

void UDriveSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bEngineRunning) return;

	UpdateRPM(DeltaTime);
	UpdateEngineTemperature(DeltaTime);
	UpdateFuelConsumption();
}

void UDriveSystem::SetThrottleInput(float Input)
{
	ThrottleInput = FMath::Clamp(Input, 0.0f, 1.0f);
}

void UDriveSystem::SetBrakeInput(float Input)
{
	BrakeInput = FMath::Clamp(Input, 0.0f, 1.0f);
}

void UDriveSystem::SetSteeringInput(float Input)
{
	SteeringInput = FMath::Clamp(Input, -1.0f, 1.0f);
}

void UDriveSystem::ShiftGearUp()
{
	if (GetWorld()->GetTimeSeconds() - LastGearShiftTime > GearShiftCooldown)
	{
		if (CurrentGear < 5)
		{
			CurrentGear++;
			LastGearShiftTime = GetWorld()->GetTimeSeconds();
		}
	}
}

void UDriveSystem::ShiftGearDown()
{
	if (GetWorld()->GetTimeSeconds() - LastGearShiftTime > GearShiftCooldown)
	{
		if (CurrentGear > -1)
		{
			CurrentGear--;
			LastGearShiftTime = GetWorld()->GetTimeSeconds();
		}
	}
}

void UDriveSystem::StartEngine()
{
	bEngineRunning = true;
	CurrentRPM = IdleRPM;
}

void UDriveSystem::StopEngine()
{
	bEngineRunning = false;
	CurrentRPM = 0.0f;
}

void UDriveSystem::AutomaticGearShift(float DeltaTime)
{
	// Logique de transmission automatique simple
	if (CurrentGear < 5 && CurrentRPM > MaxRPM * 0.9f)
	{
		ShiftGearUp();
	}
	else if (CurrentGear > 1 && CurrentRPM < MaxRPM * 0.3f && ThrottleInput < 0.1f)
	{
		ShiftGearDown();
	}
}

void UDriveSystem::UpdateRPM(float DeltaTime)
{
	float TargetRPM = IdleRPM;

	if (ThrottleInput > 0.0f)
	{
		TargetRPM = IdleRPM + (MaxRPM - IdleRPM) * ThrottleInput;
	}

	// Interpolation lisse du RPM
	CurrentRPM = FMath::Lerp(CurrentRPM, TargetRPM, EngineInertia * DeltaTime);
}

void UDriveSystem::UpdateEngineTemperature(float DeltaTime)
{
	float RPMRatio = CurrentRPM / MaxRPM;
	float TargetTemp = 20.0f + (NormalTemp - 20.0f) * RPMRatio;

	EngineTemperature = FMath::Lerp(EngineTemperature, TargetTemp, DeltaTime * 0.1f);

	// Limitation de la température
	if (EngineTemperature > MaxTemp)
	{
		EngineTemperature = MaxTemp;
		CurrentRPM = IdleRPM; // Moteur surchauffé
	}
}

void UDriveSystem::UpdateFuelConsumption()
{
	FuelConsumption = IdleFuelConsumption + (ThrottleInput * (CurrentRPM / MaxRPM));
}

float UDriveSystem::CalculateEngineTorque(float RPM)
{
	// Courbe de couple simplifiée
	float RPMRatio = RPM / MaxRPM;
	float TorqueCurve = (1.0f - (RPMRatio * RPMRatio)) * MaxEnginePower;
	return TorqueCurve;
}
