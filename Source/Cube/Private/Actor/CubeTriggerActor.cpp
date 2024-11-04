// Copyright EderSantander developer


#include "Actor/CubeTriggerActor.h"

#include "Actor/CubeSplineMeshActor.h"
#include "Components/BoxComponent.h"

ACubeTriggerActor::ACubeTriggerActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(BoxComponent);
}

void ACubeTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACubeTriggerActor::OnBeginOverlap);
}

void ACubeTriggerActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TriggerType == ETriggerActorType::OneShot)
	{
		const int32 SplineNumber = SpawnSplines.Num();
		for (ACubeSplineMeshActor* Spline : SpawnSplines)
		{
			Spline->SpawnActorsOnSpline();
		}
		BoxComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}
