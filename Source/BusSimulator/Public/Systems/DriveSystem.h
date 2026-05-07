#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DriveSystem.generated.h"

class ABusVehicle;

/**
 * Système de transmission et moteur du bus
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUSSIMULATOR_API UDriveSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UDriveSystem();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ========== ENTRÉES UTILISATEUR ==========
	void SetThrottleInput(float Input);
	void SetBrakeInput(float Input);
	void SetSteeringInput(float Input);
	void ShiftGearUp();
	void ShiftGearDown();
	void StartEngine();
	void StopEngine();

	// ========== GETTERS ==========
	float FORCEINLINE GetThrottleInput() const { return ThrottleInput; }
	float FORCEINLINE GetBrakeInput() const { return BrakeInput; }
	float FORCEINLINE GetSteeringInput() const { return SteeringInput; }
	float FORCEINLINE GetRPM() const { return CurrentRPM; }
	int32 FORCEINLINE GetCurrentGear() const { return CurrentGear; }
	float FORCEINLINE GetEngineTemperature() const { return EngineTemperature; }
	float FORCEINLINE GetFuelConsumption() const { return FuelConsumption; }
	bool FORCEINLINE IsEngineRunning() const { return bEngineRunning; }

	// ========== TRANSMISSION AUTOMATIQUE ==========
	void AutomaticGearShift(float DeltaTime);

	// ========== PARAMÈTRES MOTEUR ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float MaxRPM = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float IdleRPM = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float EngineInertia = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float MaxEnginePower = 300000.0f; // Watts

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuel")
	float IdleFuelConsumption = 0.05f; // L/s

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temperature")
	float NormalTemp = 90.0f; // Celsius

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temperature")
	float MaxTemp = 120.0f; // Celsius

protected:
	// ========== RÉFÉRENCES ==========
	ABusVehicle* BusOwner;

	// ========== ENTRÉES ==========
	float ThrottleInput;
	float BrakeInput;
	float SteeringInput;

	// ========== ÉTAT MOTEUR ==========
	float CurrentRPM;
	int32 CurrentGear; // -1=Reverse, 0=Neutral, 1-5=Gears
	bool bEngineRunning;
	float EngineTemperature;
	float FuelConsumption;

	// ========== TEMPS ==========
	float GearShiftCooldown;
	float LastGearShiftTime;

	// ========== CALCULS ==========
	void UpdateRPM(float DeltaTime);
	void UpdateEngineTemperature(float DeltaTime);
	void UpdateFuelConsumption();
	float CalculateEngineTorque(float RPM);
};
