// Copyright EderSantander developer


#include "Actor/CubeShooterActor.h"

#include "AbilitySystemComponent/CubeAbilitySystemFunctionLibrary.h"
#include "Actor/CubeProjectileActor.h"

ACubeShooterActor::ACubeShooterActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void ACubeShooterActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACubeShooterActor::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnEnemies"));
	TArray<FVector> Directions = UCubeAbilitySystemFunctionLibrary::EvenlySpreadVectors(GetActorForwardVector(), FVector::ZAxisVector, SpreadAngle,NumProjectiles);
	for (auto Direction : Directions)
	{
		FVector ProjectileOrigin = GetActorLocation() + Direction * DistanceFromActor;
		FRotator Rotation = Direction.Rotation();
		DrawDebugSphere(GetWorld(), ProjectileOrigin, 20.f, 12, FColor::Red, false, 5.0f);
		//GetWorld()->SpawnActor<ProjectileClass>(this->GetClass(), myLoc, myRot, SpawnInfo);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ACubeProjectileActor>(ProjectileClass, ProjectileOrigin, Rotation, SpawnParameters);
	}
}

