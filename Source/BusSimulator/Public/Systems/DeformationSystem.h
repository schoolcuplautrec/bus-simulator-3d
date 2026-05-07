#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeformationSystem.generated.h"

/**
 * Système de déformation en temps réel du bus
 * Déformation des panneaux, portes, vitres, etc.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUSSIMULATOR_API UDeformationSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UDeformationSystem();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ========== DÉFORMATION ==========
	UFUNCTION(BlueprintCallable, Category = "Deformation")
	void DeformPanel(int32 PanelIndex, FVector DeformationDirection, float Intensity);

	UFUNCTION(BlueprintCallable, Category = "Deformation")
	void BreakWindow(int32 WindowIndex);

	UFUNCTION(BlueprintCallable, Category = "Deformation")
	void DamageDoor(int32 DoorIndex, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Deformation")
	void BendFrame(FVector BendDirection, float Intensity);

	// ========== GETTERS ==========
	UFUNCTION(BlueprintCallable, Category = "Deformation")
	bool IsWindowBroken(int32 WindowIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Deformation")
	float GetPanelDeformation(int32 PanelIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Deformation")
	int32 GetBrokenWindowCount() const;

	// ========== PARAMÈTRES ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	int32 MaxPanels = 8; // Nombre de panneaux déformables

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	int32 MaxWindows = 12; // Nombre de vitres

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	int32 MaxDoors = 3; // Nombre de portes

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	float MaxPanelDeformation = 100.0f; // Déformation maximale d'un panneau (cm)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Deformation")
	float DeformationRecoveryRate = 5.0f; // Récupération par seconde (%)

protected:
	// ========== ÉTATS ==========
	TArray<float> PanelDeformations; // État de déformation de chaque panneau (0-100)
	TArray<bool> WindowsBroken; // État des vitres cassées
	TArray<float> DoorHealth; // Santé de chaque porte

	// ========== FRAME ==========
	float FrameBend = 0.0f; // Courbure du châssis (-100 à 100)
	bool bFrameBent = false; // Le châssis est-il plié?
};
