#include "Systems/DeformationSystem.h"

UDeformationSystem::UDeformationSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	PanelDeformations.SetNum(MaxPanels);
	WindowsBroken.SetNum(MaxWindows);
	DoorHealth.SetNum(MaxDoors);

	// Initialiser les états
	for (int32 i = 0; i < MaxPanels; ++i)
	{
		PanelDeformations[i] = 0.0f;
	}

	for (int32 i = 0; i < MaxWindows; ++i)
	{
		WindowsBroken[i] = false;
	}

	for (int32 i = 0; i < MaxDoors; ++i)
	{
		DoorHealth[i] = 100.0f;
	}
}

void UDeformationSystem::BeginPlay()
{
	Super::BeginPlay();
}

void UDeformationSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Récupération progressive des déformations
	for (int32 i = 0; i < PanelDeformations.Num(); ++i)
	{
		if (PanelDeformations[i] > 0.0f)
		{
			PanelDeformations[i] -= DeformationRecoveryRate * DeltaTime;
			PanelDeformations[i] = FMath::Max(0.0f, PanelDeformations[i]);
		}
	}
}

void UDeformationSystem::DeformPanel(int32 PanelIndex, FVector DeformationDirection, float Intensity)
{
	if (PanelIndex >= 0 && PanelIndex < MaxPanels)
	{
		PanelDeformations[PanelIndex] += Intensity;
		PanelDeformations[PanelIndex] = FMath::Clamp(PanelDeformations[PanelIndex], 0.0f, MaxPanelDeformation);

		UE_LOG(LogTemp, Warning, TEXT("Panel %d deformed: %.2f"), PanelIndex, PanelDeformations[PanelIndex]);
	}
}

void UDeformationSystem::BreakWindow(int32 WindowIndex)
{
	if (WindowIndex >= 0 && WindowIndex < MaxWindows)
	{
		WindowsBroken[WindowIndex] = true;
		UE_LOG(LogTemp, Warning, TEXT("Window %d is BROKEN!"), WindowIndex);
	}
}

void UDeformationSystem::DamageDoor(int32 DoorIndex, float DamageAmount)
{
	if (DoorIndex >= 0 && DoorIndex < MaxDoors)
	{
		DoorHealth[DoorIndex] -= DamageAmount;
		DoorHealth[DoorIndex] = FMath::Max(0.0f, DoorHealth[DoorIndex]);

		if (DoorHealth[DoorIndex] <= 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Door %d is DESTROYED!"), DoorIndex);
		}
	}
}

void UDeformationSystem::BendFrame(FVector BendDirection, float Intensity)
{
	FrameBend += Intensity;
	FrameBend = FMath::Clamp(FrameBend, -100.0f, 100.0f);

	if (FMath::Abs(FrameBend) > 50.0f)
	{
		bFrameBent = true;
		UE_LOG(LogTemp, Error, TEXT("FRAME IS SEVERELY BENT! Handling compromised!"));
	}
}

bool UDeformationSystem::IsWindowBroken(int32 WindowIndex) const
{
	if (WindowIndex >= 0 && WindowIndex < MaxWindows)
	{
		return WindowsBroken[WindowIndex];
	}
	return false;
}

float UDeformationSystem::GetPanelDeformation(int32 PanelIndex) const
{
	if (PanelIndex >= 0 && PanelIndex < MaxPanels)
	{
		return (PanelDeformations[PanelIndex] / MaxPanelDeformation) * 100.0f;
	}
	return 0.0f;
}

int32 UDeformationSystem::GetBrokenWindowCount() const
{
	int32 Count = 0;
	for (bool bBroken : WindowsBroken)
	{
		if (bBroken) Count++;
	}
	return Count;
}
