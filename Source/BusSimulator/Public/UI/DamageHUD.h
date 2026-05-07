#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageHUD.generated.h"

class ABusVehicle;
class UDamageSystem;

/**
 * HUD d'affichage des dégâts
 */
UCLASS()
class BUSSIMULATOR_API UDamageHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	void SetBusReference(ABusVehicle* InBus);

	// ========== GETTERS POUR AFFICHAGE ==========
	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	float GetBodyDamagePercent() const;

	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	float GetEngineDamagePercent() const;

	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	float GetSuspensionDamagePercent(int32 WheelIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	int32 GetBrokenWindowCount() const;

	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	bool IsEngineDestroyed() const;

	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	bool IsWheelDamaged(int32 WheelIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Damage HUD")
	FString GetDamageStatus() const;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	ABusVehicle* BusReference;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UDamageSystem* DamageSystem;
};
