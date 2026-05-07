#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToulouseEnvironment.generated.h"

class UStaticMeshComponent;
class UMaterialInstance;

/**
 * Environnement de Toulouse - Générateur de buildings et routes
 */
AACTOR_API UCLASS()
class BUSSIMULATOR_API AToulouseEnvironment : public AActor
{
	GENERATED_BODY()

public:
	AToulouseEnvironment();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ========== COMPOSANTS ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RoadMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<UStaticMeshComponent*> Buildings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<UStaticMeshComponent*> Streetlights;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<UStaticMeshComponent*> Trees;

	// ========== MATÉRIAUX ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* RoadMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* BrickMaterial; // Briques rouges de Toulouse

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* StoneMaterial;

	// ========== DONNÉES ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Data")
	float MapWidth = 10000.0f; // cm (100m)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Data")
	float MapHeight = 10000.0f; // cm (100m)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Data")
	int32 BuildingDensity = 40; // % de la map avec bâtiments

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment Data")
	FColor ToulouseRedColor = FColor(180, 70, 70, 255); // Couleur de brique

	// ========== MÉTHODES ==========
	UFUNCTION(BlueprintCallable, Category = "Environment")
	void GenerateBuildings();

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void GenerateRoads();

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void SpawnStreetElements();

private:
	void CreateBuildingBlock(FVector Position, FVector Scale);
	void CreateStreetlight(FVector Position);
	void CreateTree(FVector Position);
};
