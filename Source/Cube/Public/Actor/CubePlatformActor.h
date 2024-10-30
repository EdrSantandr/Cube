// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubePlatformActor.generated.h"

class UMovementComponent;
class UBoxComponent;

UCLASS()
class CUBE_API ACubePlatformActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACubePlatformActor();

	UFUNCTION(BlueprintImplementableEvent)
	void MaterialEffect();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, Category="Platform")
	float WarningTime = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UMovementComponent> MovementComponent;

private:
	FTimerHandle WarningTimerHandle;
	FTimerDelegate WarningDelegate;

	UFUNCTION()
	void Warning_Elapsed() const;
};
