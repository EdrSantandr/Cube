// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeSplineMeshActor.generated.h"

class USplineComponent;

UENUM(BlueprintType)
enum class ESplineActorType : uint8
{
	OneShot,
	Loop,
	Multiple
};

UCLASS()
class CUBE_API ACubeSplineMeshActor : public AActor
{
	GENERATED_BODY()
	
public:

	ACubeSplineMeshActor();
	
	UPROPERTY(EditAnywhere, Category="Blocking")
	TSubclassOf<AActor> BlockingClass;

	UPROPERTY(EditDefaultsOnly, Category="Blocking")
	ESplineActorType InteractionType = ESplineActorType::OneShot;

	UPROPERTY(EditDefaultsOnly, Category="Blocking")
	float StartInteractionTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Blocking")
	float InteractionTime = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Blocking")
	bool AutoSpawn = false;
	
	UFUNCTION(BlueprintCallable, Category="Blocking")
	void SpawnActorsOnSpline();

	UFUNCTION(BlueprintImplementableEvent, Category="Blocking")
	void MoveSpawnedBlockingOneShot();

	UFUNCTION(BlueprintImplementableEvent, Category="Blocking")
	void MoveSpawnedBlockingLoop();

	UFUNCTION(BlueprintCallable, Category="Blocking")
	AActor* GetSpawnedActor() { return SpawnedActor; }

	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USplineComponent> SplineComponent;

	UFUNCTION()
	void InteractionStart();

private:
	FTimerHandle InteractionTimerHandle;
	FTimerDelegate InteractionTimerDelegate;

	UPROPERTY()
	TObjectPtr<AActor> SpawnedActor = nullptr;
	
};
