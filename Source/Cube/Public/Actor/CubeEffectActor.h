// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeEffectActor.generated.h"

class UBoxComponent;

UCLASS()
class CUBE_API ACubeEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	ACubeEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
