// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeTriggerActor.generated.h"

class ACubeSplineMeshActor;
class UBoxComponent;

UCLASS()
class CUBE_API ACubeTriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACubeTriggerActor();

	UPROPERTY(EditAnywhere, Category="Blocking")
	TArray<ACubeSplineMeshActor*> SpawnSplines;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
