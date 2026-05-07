#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BusConfigData.generated.h"

/**
 * Configuration de différents types de bus
 */
UENUM(BlueprintType)
enum class EBusType : uint8
{
	StandardBus UMETA(DisplayName = "Standard Bus (Citaro/Volvo B7)"),
	AriculatedBus UMETA(DisplayName = "Articulated Bus (with Trailer)"),
	MiniBus UMETA(DisplayName = "Mini Bus")
};

/**
 * Asset de configuration pour les données de bus
 */
UCLASS()
class BUSSIMULATOR_API UBusConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	// ========== TYPE DE BUS ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Config")
	EBusType BusType = EBusType::StandardBus;

	// ========== DIMENSIONS ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
	float BusLength = 1200.0f; // cm (12m pour standard, 18m pour articulé)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
	float BusWidth = 250.0f; // cm (2.5m standard)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dimensions")
	float BusHeight = 350.0f; // cm (3.5m standard)

	// ========== CAPACITÉ ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	int32 MaxPassengers = 100; // Assises + debout

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	int32 SeatedPassengers = 60;

	// ========== COULEUR ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FColor BusMainColor = FColor(200, 50, 50, 255); // Rouge Toulouse

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FColor BusAccentColor = FColor(255, 255, 255, 255); // Blanc

	// ========== DONNÉES MOTEUR PERSONNALISÉES ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float MaxEnginePower = 300000.0f; // Watts (300 kW)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float MaxRPM = 2500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Engine")
	float BusMass = 12000.0f; // kg (varie selon type)

	// ========== DESCRIPTIONS ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
	FString BusName = TEXT("Standard City Bus");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Description")
	FString Manufacturer = TEXT("Mercedes-Benz Citaro");
};
