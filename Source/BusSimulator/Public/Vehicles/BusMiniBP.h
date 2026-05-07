#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BusMiniBP.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UMaterialInstance;

/**
 * Mini-Bus - 8-10m (bus de proximity/navette)
 */
AACTOR_API UCLASS()
class BUSSIMULATOR_API ABusMiniBP : public AActor
{
	GENERATED_BODY()

public:
	ABusMiniBP();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ========== CARROSSERIE ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* BusBody;

	// ========== ROUES ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FrontWheel_Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FrontWheel_Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RearWheel_Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RearWheel_Right;

	// ========== PORTES ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FrontDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RearDoor;

	// ========== MATÉRIAUX ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* BusBodyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* WheelMaterial;

	// ========== DONNÉES ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float BusLength = 1000.0f; // 10m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float BusWidth = 230.0f; // 2.3m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float BusHeight = 320.0f; // 3.2m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	int32 MaxPassengers = 50; // Plus petit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float Mass = 7500.0f; // Plus léger

private:
	void SetupMeshes();
	void SetupMaterials();
};
