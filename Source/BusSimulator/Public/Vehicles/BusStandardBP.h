#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BusStandardBP.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UMaterialInstance;

/**
 * Bus Standard Urbain - Citaro/Volvo B7 (12m)
 */
AACTOR_API UCLASS()
class BUSSIMULATOR_API ABusStandardBP : public AActor
{
	GENERATED_BODY()

public:
	ABusStandardBP();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ========== COMPOSANTS VISUELS ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* BusBody;

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
	UStaticMeshComponent* MiddleDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RearDoor;

	// ========== FENÃTRES ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<UStaticMeshComponent*> Windows;

	// ========== MATÉRIAUX ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* BusBodyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* WheelMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstance* WindowMaterial;

	// ========== DONNÉES ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float BusLength = 1200.0f; // 12m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float BusWidth = 250.0f; // 2.5m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	float BusHeight = 350.0f; // 3.5m

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	int32 MaxPassengers = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	FColor PrimaryColor = FColor(200, 50, 50, 255); // Rouge

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bus Data")
	FColor SecondaryColor = FColor(255, 255, 255, 255); // Blanc

private:
	void SetupMeshes();
	void SetupMaterials();
	void SetupDoors();
	void SetupWindows();
};
