#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BusVehicle.generated.h"

class UPhysicsSystem;
class UDriveSystem;
class UBusHUD;
class USpringArmComponent;
class UCameraComponent;
class USkeletalMeshComponent;

/**
 * Classe principale du bus - Simulateur de conduite
 */
UCLASS()
class BUSSIMULATOR_API ABusVehicle : public APawn
{
	GENERATED_BODY()

protected:
	// ========== COMPOSANTS ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* BusMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
	UPhysicsSystem* PhysicsSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
	UDriveSystem* DriveSystem;

	// ========== HUD ==========
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UBusHUD* BusHUD;

	// ========== PARAMÈTRES MOTEUR ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float MaxEnginePower = 300000.0f; // Watts (300 kW)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float MaxRPM = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float IdleRPM = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float EngineInertia = 5.0f;

	// ========== TRANSMISSION ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmission")
	float GearRatio1 = 4.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmission")
	float GearRatio2 = 2.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmission")
	float GearRatio3 = 1.9f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmission")
	float GearRatio4 = 1.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmission")
	float GearRatio5 = 0.9f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmission")
	float GearRatioReverse = 4.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transmission")
	float FinalDriveRatio = 3.5f;

	// ========== SUSPENSION & FREINAGE ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension")
	float SuspensionStiffness = 50000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension")
	float SuspensionDamping = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brakes")
	float MaxBrakeTorque = 8000.0f;

	// ========== DIRECTION ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Steering")
	float MaxSteeringAngle = 45.0f; // Degrés

	// ========== MASSE & DIMENSIONS ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float BusMass = 12000.0f; // kg

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float AirResistanceFactor = 0.65f; // Cd

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float RollingResistanceFactor = 0.015f;

	// ========== CARBURANT ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float MaxFuelCapacity = 100.0f; // Litres

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float FuelConsumptionRate = 0.05f; // L/s au ralenti

	// ========== VARIABLES D'ÉTAT ==========
	UPROPERTY(BlueprintReadOnly, Category = "State")
	float CurrentRPM;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	int32 CurrentGear;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	float EngineTemperature;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	float FuelLevel;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsEngineRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bUseAutomaticTransmission;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bInternalCamera;

public:
	ABusVehicle();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ========== GETTERS ==========
	UFUNCTION(BlueprintCallable, Category = "Bus")
	float GetCurrentRPM() const;

	UFUNCTION(BlueprintCallable, Category = "Bus")
	float GetCurrentSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Bus")
	int32 GetCurrentGear() const;

	UFUNCTION(BlueprintCallable, Category = "Bus")
	float GetEngineTemperature() const;

	UFUNCTION(BlueprintCallable, Category = "Bus")
	float GetFuelLevel() const;
};
