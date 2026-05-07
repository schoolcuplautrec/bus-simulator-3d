#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelStreamingDynamic.h"
#include "ToulouseMapManager.generated.h"

class AToulouseEnvironment;

/**
 * Gestionnaire de la map de Toulouse
 */
UCLASS()
class BUSSIMULATOR_API UToulouseMapManager : public UObject
{
	GENERATED_BODY()

public:
	UToulouseMapManager();

	// ========== ZONES DE TOULOUSE ==========
	ENUM(BlueprintType)
	enum class EToulouseDistrict : uint8
	{
		VieuxToulouse UMETA(DisplayName = "Vieux Toulouse"),
		PlaceCapitole UMETA(DisplayName = "Place du Capitole"),
		PontNeuf UMETA(DisplayName = "Pont Neuf"),
		AlleeJulesMichelet UMETA(DisplayName = "Allee Jules Michelet"),
		Aeroparc UMETA(DisplayName = "Aerospatiale"),
		BayonneQuartier UMETA(DisplayName = "Bayonne Quartier")
	};

	// ========== MÉTHODES ==========
	UFUNCTION(BlueprintCallable, Category = "Map Management")
	void GenerateMapLayout();

	UFUNCTION(BlueprintCallable, Category = "Map Management")
	void LoadDistrict(EToulouseDistrict District);

	UFUNCTION(BlueprintCallable, Category = "Map Management")
	void SpawnBuildings();

	UFUNCTION(BlueprintCallable, Category = "Map Management")
	void SetupRoads();

	UFUNCTION(BlueprintCallable, Category = "Map Management")
	void SpawnStreetEnvironment();

	// ========== DONNÉES MAP ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	FVector MapCenter = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	float MapScale = 1.0f; // Échelle par rapport à Toulouse réelle

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	int32 GridCellSize = 1000; // cm (10m)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	int32 MapWidth = 100; // nombre de cellules

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Data")
	int32 MapHeight = 100; // nombre de cellules
};
