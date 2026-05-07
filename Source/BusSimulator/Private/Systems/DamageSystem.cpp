#include "Systems/DamageSystem.h"
#include "Vehicles/BusVehicle.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

UDamageSystem::UDamageSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	BodyIntegrity = MaxBodyIntegrity;
	EngineHealth = MaxEngineHealth;
	TransmissionHealth = MaxTransmissionHealth;

	SuspensionHealth.SetNum(4);
	WheelDamaged.SetNum(4);

	for (int32 i = 0; i < 4; ++i)
	{
		SuspensionHealth[i] = MaxSuspensionHealth;
		WheelDamaged[i] = false;
	}
}

void UDamageSystem::BeginPlay()
{
	Super::BeginPlay();
	BusOwner = Cast<ABusVehicle>(GetOwner());
}

void UDamageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!BusOwner) return;

	// Vérifier l'état du moteur
	CheckEngineFailure();
	UpdateVisualDamage();

	// Gestion du feu
	if (bEngineOnFire)
	{
		EngineHealth -= DeltaTime * 10.0f; // Perte progressive de santé
	}
}

void UDamageSystem::ApplyImpactDamage(FVector ImpactPoint, FVector ImpactForce, float ImpactEnergy)
{
	if (!BusOwner) return;

	// Calculer les dégâts d'impact
	float Damage = CalculateImpactDamage(ImpactEnergy, ImpactForce.GetSafeNormal());
	Damage *= CrashImpactMultiplier;

	// Appliquer les dégâts à la carrosserie
	BodyIntegrity -= Damage;
	BodyIntegrity = FMath::Max(0.0f, BodyIntegrity);

	// Sauvegarder les données d'impact
	LastImpactEnergy = ImpactEnergy;
	LastImpactDirection = ImpactForce.GetSafeNormal();
	LastImpactAngle = FMath::Acos(FVector::DotProduct(LastImpactDirection, FVector::UpVector));

	// Appliquer la déformation
	ApplyDeformation(ImpactPoint, Damage);

	// Vérifier si le moteur est endommagé
	if (ImpactEnergy > 5000.0f) // Collision importante
	{
		EngineHealth -= Damage * 0.5f;
	}

	// Vérifier si la transmission est endommagée
	if (ImpactEnergy > 3000.0f)
	{
		TransmissionHealth -= Damage * 0.3f;
	}

	UE_LOG(LogTemp, Warning, TEXT("Impact Damage: %.2f | Body Health: %.2f"), Damage, BodyIntegrity);
}

void UDamageSystem::ApplyRolloverDamage(float RollbackAngle)
{
	// Dégâts de tonneau - très graves
	float DamageAmount = FMath::Abs(RollbackAngle) * RolloverDamageMultiplier;

	BodyIntegrity -= DamageAmount;
	BodyIntegrity = FMath::Max(0.0f, BodyIntegrity);

	// Dégâts du moteur lors d'un tonneau
	EngineHealth -= DamageAmount * 0.6f;

	// Tous les amortisseurs sont endommagés
	for (int32 i = 0; i < 4; ++i)
	{
		SuspensionHealth[i] -= DamageAmount * 0.4f;
		CheckWheelDamage(i);
	}

	UE_LOG(LogTemp, Warning, TEXT("Rollover Damage: %.2f | Angle: %.2f degrees"), DamageAmount, RollbackAngle);
}

void UDamageSystem::ApplySuspensionDamage(float Compression, int32 WheelIndex)
{
	if (WheelIndex < 0 || WheelIndex >= 4) return;

	// Si la compression est trop importante, endommager la suspension
	if (Compression > SuspensionBreakThreshold)
	{
		float DamageAmount = (Compression - SuspensionBreakThreshold) * 0.5f;
		SuspensionHealth[WheelIndex] -= DamageAmount;
		CheckWheelDamage(WheelIndex);

		UE_LOG(LogTemp, Warning, TEXT("Suspension Damage on Wheel %d: %.2f"), WheelIndex, DamageAmount);
	}
}

void UDamageSystem::ApplyFireDamage(float Temperature)
{
	EngineTemperature = Temperature;

	if (Temperature > EngineFireThreshold && !bEngineOnFire)
	{
		bEngineOnFire = true;
		UE_LOG(LogTemp, Warning, TEXT("ENGINE ON FIRE! Temperature: %.2f°C"), Temperature);
	}

	if (bEngineOnFire)
	{
		EngineHealth -= Temperature * 0.1f;
	}
}

float UDamageSystem::GetOverallHealthPercentage() const
{
	float TotalHealth = BodyIntegrity + EngineHealth + TransmissionHealth;
	float MaxTotal = MaxBodyIntegrity + MaxEngineHealth + MaxTransmissionHealth;

	return FMath::Max(0.0f, (TotalHealth / MaxTotal) * 100.0f);
}

float UDamageSystem::GetSuspensionDamage(int32 WheelIndex) const
{
	if (WheelIndex >= 0 && WheelIndex < 4)
	{
		return MaxSuspensionHealth - SuspensionHealth[WheelIndex];
	}
	return 0.0f;
}

bool UDamageSystem::IsWheelDamaged(int32 WheelIndex) const
{
	if (WheelIndex >= 0 && WheelIndex < 4)
	{
		return WheelDamaged[WheelIndex];
	}
	return false;
}

float UDamageSystem::CalculateImpactDamage(float ImpactEnergy, FVector ImpactDirection)
{
	// Formule de dégâts inspirée de BeamNG
	// Dégâts = Énergie d'impact * Angle d'impact * Facteur de sévérité

	float AngleFactor = 1.0f - FMath::Abs(FVector::DotProduct(ImpactDirection, FVector::UpVector));
	float DamageAmount = ImpactEnergy * AngleFactor * 0.01f;

	return DamageAmount;
}

void UDamageSystem::ApplyDeformation(FVector ImpactPoint, float DamageAmount)
{
	// Sauvegarder le point de déformation
	FVector LocalImpactPoint = BusOwner->GetActorTransform().Inverse().TransformPosition(ImpactPoint);
	DeformationPoints.Add(LocalImpactPoint);

	// Augmenter la déformation globale
	GlobalDeformation += DamageAmount * 0.1f;
	GlobalDeformation = FMath::Clamp(GlobalDeformation, 0.0f, 100.0f);
}

void UDamageSystem::CheckWheelDamage(int32 WheelIndex)
{
	if (WheelIndex >= 0 && WheelIndex < 4)
	{
		if (SuspensionHealth[WheelIndex] <= 0.0f)
		{
			WheelDamaged[WheelIndex] = true;
			UE_LOG(LogTemp, Warning, TEXT("Wheel %d is DESTROYED!"), WheelIndex);
		}
	}
}

void UDamageSystem::UpdateVisualDamage()
{
	if (!BusOwner) return;

	// Mettre à jour les matériaux du bus pour montrer les dégâts
	if (BodyIntegrity < MaxBodyIntegrity * 0.5f)
	{
		// Dégâts significatifs - changer couleur/matériau
	}

	if (bEngineOnFire)
	{
		// Afficher des effets de feu
	}
}

void UDamageSystem::CheckEngineFailure()
{
	if (EngineHealth <= 0.0f)
	{
		if (BusOwner && BusOwner->DriveSystem)
		{
			BusOwner->DriveSystem->StopEngine();
			UE_LOG(LogTemp, Error, TEXT("ENGINE DESTROYED - Vehicle stopped"));
		}
	}
}
