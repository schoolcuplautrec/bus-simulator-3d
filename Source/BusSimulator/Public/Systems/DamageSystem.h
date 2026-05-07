#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystem.generated.h"

/**
 * Types de dégâts
 */
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Collision UMETA(DisplayName = "Collision"),
	Rollover UMETA(DisplayName = "Rollover (Tonneau)"),
	Deformation UMETA(DisplayName = "Deformation"),
	FireDamage UMETA(DisplayName = "Fire Damage"),
	SuspensionBreak UMETA(DisplayName = "Suspension Break")
};

/**
 * Système de dégâts réaliste inspiré de BeamNG Drive
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUSSIMULATOR_API UDamageSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UDamageSystem();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ========== INFLICTER DES DÉGÂTS ==========
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyImpactDamage(FVector ImpactPoint, FVector ImpactForce, float ImpactEnergy);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyRolloverDamage(float RollbackAngle);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplySuspensionDamage(float Compression, int32 WheelIndex);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ApplyFireDamage(float Temperature);

	// ========== GETTERS ==========
	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetOverallHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetBodyDamage() const { return BodyIntegrity; }

	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetEngineDamage() const { return EngineHealth; }

	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetSuspensionDamage(int32 WheelIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool IsWheelDamaged(int32 WheelIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool IsEngineDestroyed() const { return EngineHealth <= 0.0f; }

	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool IsTransmissionBroken() const { return TransmissionHealth <= 10.0f; }

	// ========== PARAMÈTRES DÉGÂTS ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
	float MaxBodyIntegrity = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
	float MaxEngineHealth = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
	float MaxSuspensionHealth = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
	float MaxTransmissionHealth = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
	float CrashImpactMultiplier = 1.5f; // Plus de dégâts lors d'impacts

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
	float RolloverDamageMultiplier = 2.0f; // Dégâts de tonneau (double)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Parameters")
	float SuspensionBreakThreshold = 150.0f; // Compression max avant casse

protected:
	// ========== RÉFÉRENCES ==========
	class ABusVehicle* BusOwner;

	// ========== ÉTATS DE SANTÉ ==========
	float BodyIntegrity; // Intégrité de la carrosserie
	float EngineHealth; // Santé du moteur
	float TransmissionHealth; // Santé de la transmission
	TArray<float> SuspensionHealth; // Santé pour chaque roue
	TArray<bool> WheelDamaged; // État endommagé des roues

	// ========== DÉFORMATION ==========
	TArray<FVector> DeformationPoints; // Points de déformation
	float GlobalDeformation = 0.0f; // Déformation globale

	// ========== DONNÉES D'IMPACT ==========
	float LastImpactEnergy = 0.0f;
	float LastImpactAngle = 0.0f;
	FVector LastImpactDirection = FVector::ZeroVector;

	// ========== FOURNISSEUR ==========
	float EngineTemperature = 90.0f;
	float EngineFireThreshold = 150.0f; // Température avant incendie
	bool bEngineOnFire = false;

	// ========== CALCULS ==========
	float CalculateImpactDamage(float ImpactEnergy, FVector ImpactDirection);
	void ApplyDeformation(FVector ImpactPoint, float DamageAmount);
	void CheckWheelDamage(int32 WheelIndex);
	void UpdateVisualDamage();
	void CheckEngineFailure();
};
