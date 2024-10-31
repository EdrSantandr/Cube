// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ShooterInterface.h"
#include "CubeShooterActor.generated.h"

class ACubeProjectileActor;

UCLASS()
class CUBE_API ACubeShooterActor : public AActor, public IShooterInterface
{
	GENERATED_BODY()
	
public:	
	ACubeShooterActor();

	/*Shooter interface*/
	virtual void PerformShoot_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, Category="Projectile")
	TSubclassOf<ACubeProjectileActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float DistanceFromActor = 50.f;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	int32 NumProjectiles = 5;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float SpreadAngle = 90.f;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Shoot();
};
