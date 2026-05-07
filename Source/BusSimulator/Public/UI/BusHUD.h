#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BusHUD.generated.h"

class ABusVehicle;

/**
 * HUD du bus - Interface utilisateur
 */
UCLASS()
class BUSSIMULATOR_API UBusHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void SetBusReference(ABusVehicle* InBus);

	// ========== GETTERS POUR BLUEPRINT ==========
	UFUNCTION(BlueprintCallable, Category = "HUD")
	float GetDisplaySpeed() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	float GetDisplayRPM() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	int32 GetDisplayGear() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	float GetDisplayFuel() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	float GetDisplayTemperature() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	FString GetGearString() const;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	ABusVehicle* BusReference;

	// ========== CONVERTISSEURS ==========
	float ConvertSpeedKmh(float SpeedCm) const;
	float ConvertTemperatureCelsius(float RawTemp) const;
};
