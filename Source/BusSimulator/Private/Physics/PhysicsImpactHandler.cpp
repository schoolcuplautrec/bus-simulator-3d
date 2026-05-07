#include "Physics/PhysicsImpactHandler.h"
#include "Vehicles/BusVehicle.h"
#include "Systems/DamageSystem.h"
#include "Components/PrimitiveComponent.h"

APhysicsImpactHandler::APhysicsImpactHandler()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APhysicsImpactHandler::BeginPlay()
{
	Super::BeginPlay();
}

void APhysicsImpactHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicsImpactHandler::OnBusComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HitComponent) return;

	// Calculer l'énergie d'impact
	float ImpactEnergy = NormalImpulse.Length();

	if (ImpactEnergy > MinImpactEnergyForDamage)
	{
		HandleCollision(OtherActor, Hit.ImpactPoint, NormalImpulse);
	}
}

void APhysicsImpactHandler::HandleCollision(AActor* OtherActor, FVector ImpactPoint, FVector ImpactForce)
{
	if (!BusOwner) return;

	float ImpactEnergy = ImpactForce.Length();
	ImpactHistory.Add(ImpactEnergy);

	// Garder seulement les 10 derniers impacts
	if (ImpactHistory.Num() > 10)
	{
		ImpactHistory.RemoveAt(0);
	}

	UE_LOG(LogTemp, Warning, TEXT("Collision detected! Energy: %.2f"), ImpactEnergy);

	// Appliquer les dégâts
	CalculateAndApplyDamage(ImpactEnergy, ImpactForce.GetSafeNormal());
}

void APhysicsImpactHandler::CalculateAndApplyDamage(float ImpactEnergy, FVector ImpactDirection)
{
	if (!BusOwner) return;

	UDamageSystem* DamageSystem = BusOwner->FindComponentByClass<UDamageSystem>();
	if (!DamageSystem) return;

	// Appliquer les dégâts en fonction de l'énergie d'impact
	if (ImpactEnergy > CrashDamageThreshold)
	{
		UE_LOG(LogTemp, Error, TEXT("SEVERE CRASH! Energy: %.2f"), ImpactEnergy);
	}

	DamageSystem->ApplyImpactDamage(FVector::ZeroVector, ImpactDirection * ImpactEnergy, ImpactEnergy);
}
