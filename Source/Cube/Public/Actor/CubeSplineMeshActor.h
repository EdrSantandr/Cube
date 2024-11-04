// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeSplineMeshActor.generated.h"

class USplineComponent;

UCLASS()
class CUBE_API ACubeSplineMeshActor : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category="Blocking")
	TSubclassOf<AActor> BlockingClass;
	
	ACubeSplineMeshActor();

	UFUNCTION(BlueprintCallable, Category="Blocking")
	void SpawnActorsOnSpline();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;
};
