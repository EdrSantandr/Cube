// Copyright EderSantander developer


#include "Actor/CubeShooterActor.h"

#include "AbilitySystemComponent/CubeAbilitySystemFunctionLibrary.h"
#include "Actor/CubeProjectileActor.h"

ACubeShooterActor::ACubeShooterActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void ACubeShooterActor::PerformShoot_Implementation()
{
	Shoot();
}

void ACubeShooterActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACubeShooterActor::Shoot()
{
	TArray<FVector> Directions = UCubeAbilitySystemFunctionLibrary::EvenlySpreadVectors(GetActorForwardVector(), FVector::ZAxisVector, SpreadAngle,NumProjectiles);
	for (auto Direction : Directions)
	{
		FVector ProjectileOrigin = GetActorLocation() + Direction * DistanceFromActor;
		FRotator Rotation = Direction.Rotation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ACubeProjectileActor>(ProjectileClass, ProjectileOrigin, Rotation, SpawnParameters);
	}
}

