#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsImpactHandler.generated.h"

class ABusVehicle;

/**
 * Gestionnaire des impacts physiques
 */
AACTOR_API UCLASS()
class BUSSIMULATOR_API APhysicsImpactHandler : public AActor
{
	GENERATED_BODY()

public:
	APhysicsImpactHandler();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ========== ÉVÉNEMENTS D'IMPACT ==========
	UFUNCTION()
	void OnBusComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category = "Physics")
	void HandleCollision(AActor* OtherActor, FVector ImpactPoint, FVector ImpactForce);

	UFUNCTION(BlueprintCallable, Category = "Physics")
	void CalculateAndApplyDamage(float ImpactEnergy, FVector ImpactDirection);

protected:
	ABusVehicle* BusOwner;

	// ========== PARAMÈTRES D'IMPACT ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float MinImpactEnergyForDamage = 1000.0f; // Énergie minimale pour causer des dégâts

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float CrashDamageThreshold = 5000.0f; // Seuil d'accident grave

	// ========== HISTORIQUE ==========
	TArray<float> ImpactHistory; // Historique des impacts récents
};
