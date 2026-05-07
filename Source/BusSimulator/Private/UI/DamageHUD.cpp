#include "UI/DamageHUD.h"
#include "Vehicles/BusVehicle.h"
#include "Systems/DamageSystem.h"

void UDamageHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDamageHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDamageHUD::SetBusReference(ABusVehicle* InBus)
{
	BusReference = InBus;
	if (InBus)
	{
		DamageSystem = InBus->FindComponentByClass<UDamageSystem>();
	}
}

float UDamageHUD::GetBodyDamagePercent() const
{
	if (!DamageSystem) return 0.0f;
	return (1.0f - (DamageSystem->GetBodyDamage() / 1000.0f)) * 100.0f;
}

float UDamageHUD::GetEngineDamagePercent() const
{
	if (!DamageSystem) return 0.0f;
	return (1.0f - (DamageSystem->GetEngineHealth() / 500.0f)) * 100.0f;
}

float UDamageHUD::GetSuspensionDamagePercent(int32 WheelIndex) const
{
	if (!DamageSystem) return 0.0f;
	return (DamageSystem->GetSuspensionDamage(WheelIndex) / 300.0f) * 100.0f;
}

int32 UDamageHUD::GetBrokenWindowCount() const
{
	// À implémenter avec le système de déformation
	return 0;
}

bool UDamageHUD::IsEngineDestroyed() const
{
	if (!DamageSystem) return false;
	return DamageSystem->IsEngineDestroyed();
}

bool UDamageHUD::IsWheelDamaged(int32 WheelIndex) const
{
	if (!DamageSystem) return false;
	return DamageSystem->IsWheelDamaged(WheelIndex);
}

FString UDamageHUD::GetDamageStatus() const
{
	if (!DamageSystem) return TEXT("No Damage");

	float Health = DamageSystem->GetOverallHealthPercentage();

	if (Health > 80.0f)
		return TEXT("🟢 Excellent");
	else if (Health > 60.0f)
		return TEXT("🟡 Good");
	else if (Health > 40.0f)
		return TEXT("🟠 Damaged");
	else if (Health > 20.0f)
		return TEXT("🔴 Severely Damaged");
	else
		return TEXT("☠️ Critical");
}
