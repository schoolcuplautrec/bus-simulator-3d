#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BusArticulatedBP.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UMaterialInstance;

/**
 * Bus Articulé - 18m (avec remorque)
 */
AACTOR_API UCLASS()
class BUSSIMULATOR_API ABusArticulatedBP : public AActor
{
	GENERATED_BODY()

public:
	ABusArticulatedBP();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ========== SECTION PRINCIPALE ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MainBusBody;

	// ========== REMORQUE ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* TrailerBody;

	// ========== ROUES ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<UStaticMeshComponent*> MainBusWheels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<UStaticMeshComponent*> TrailerWheels;

	// ========== PORTES ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<UStaticMeshComponent*> Doors;

	// ========== MATÉRIAUX ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* BusBodyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* WheelMaterial;

	// ========== DONNÉES ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float TotalLength = 1800.0f; // 18m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float BusWidth = 250.0f; // 2.5m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	int32 MaxPassengers = 160; // Plus de capacité

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float Mass = 18000.0f; // Plus lourd (remorque)

private:
	void SetupMainBus();
	void SetupTrailer();
	void SetupArticulation();
};
