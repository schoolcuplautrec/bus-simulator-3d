#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsSystem.generated.h"

class ABusVehicle;

/**
 * Système de physique réaliste pour le bus
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUSSIMULATOR_API UPhysicsSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UPhysicsSystem();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ========== FORCES APPLIQUÉES ==========
	void ApplyThrottleForce(float ThrottleInput, float CurrentRPM, int32 CurrentGear, float FinalDriveRatio);
	void ApplyBrakeForce(float BrakeInput, float MaxBrakeTorque);
	void ApplySteeringForce(float SteeringInput, float MaxSteeringAngle);

	// ========== SUSPENSION ==========
	void UpdateSuspension(float DeltaTime);

	// ========== RÉSISTANCES ==========
	void UpdateDrag(float DeltaTime);
	void UpdateRollingResistance();

	// ========== GETTERS ==========
	FLOAT FORCEINLINE GetSpeed() const { return CurrentVelocity.Length(); }
	FVECTOR FORCEINLINE GetVelocity() const { return CurrentVelocity; }
	float FORCEINLINE GetSteeringAngle() const { return CurrentSteeringAngle; }

	TArray<float> FORCEINLINE GetWheelCompressions() const { return WheelCompressions; }

	// ========== PARAMÈTRES PHYSIQUES ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float BusMass = 12000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float WheelRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float AirResistanceFactor = 0.65f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float RollingResistanceFactor = 0.015f;

protected:
	// ========== RÉFÉRENCES ==========
	ABusVehicle* BusOwner;

	// ========== ÉTAT PHYSIQUE ==========
	FVector CurrentVelocity;
	FVector CurrentAcceleration;
	float CurrentSteeringAngle;

	// ========== ADHÉRENCE DES PNEUS ==========
	float LongitudinalSlip;
	float LateralSlip;
	float TireTemperature;

	// ========== SUSPENSION ==========
	TArray<FVector> WheelPositions;
	TArray<float> WheelCompressions;

	// ========== CALCULS ==========
	float CalculateTireGrip(float Slip);
	void UpdateWheelPhysics(float DeltaTime);
};
