#include "UI/BusHUD.h"
#include "Vehicles/BusVehicle.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UBusHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBusHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UBusHUD::SetBusReference(ABusVehicle* InBus)
{
	BusReference = InBus;
}

float UBusHUD::GetDisplaySpeed() const
{
	if (!BusReference) return 0.0f;
	return ConvertSpeedKmh(BusReference->GetCurrentSpeed());
}

float UBusHUD::GetDisplayRPM() const
{
	if (!BusReference) return 0.0f;
	return BusReference->GetCurrentRPM();
}

int32 UBusHUD::GetDisplayGear() const
{
	if (!BusReference) return 0;
	return BusReference->GetCurrentGear();
}

float UBusHUD::GetDisplayFuel() const
{
	if (!BusReference) return 0.0f;
	return BusReference->GetFuelLevel();
}

float UBusHUD::GetDisplayTemperature() const
{
	if (!BusReference) return 0.0f;
	return ConvertTemperatureCelsius(BusReference->GetEngineTemperature());
}

FString UBusHUD::GetGearString() const
{
	if (!BusReference) return TEXT("N");

	int32 Gear = BusReference->GetCurrentGear();
	switch (Gear)
	{
		case -1: return TEXT("R");
		case 0: return TEXT("N");
		case 1: return TEXT("1");
		case 2: return TEXT("2");
		case 3: return TEXT("3");
		case 4: return TEXT("4");
		case 5: return TEXT("5");
		default: return TEXT("?");
	}
}

float UBusHUD::ConvertSpeedKmh(float SpeedCm) const
{
	// cm/s to km/h: * 0.036
	return SpeedCm * 0.036f;
}

float UBusHUD::ConvertTemperatureCelsius(float RawTemp) const
{
	return RawTemp; // Déjà en Celsius
}
