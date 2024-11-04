// Copyright EderSantander developer


#include "Actor/CubeSplineMeshActor.h"
#include "Components/SplineComponent.h"

ACubeSplineMeshActor::ACubeSplineMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SetRootComponent(SplineComponent);
}

void ACubeSplineMeshActor::SpawnActorsOnSpline()
{
	check(BlockingClass);
	for (int32 Index = 0; Index<SplineComponent->GetNumberOfSplinePoints() ;Index++)
	{
		const FTransform PointTransform = SplineComponent->GetTransformAtSplinePoint(Index, ESplineCoordinateSpace::World);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(BlockingClass, PointTransform, SpawnParameters);
	}
}

void ACubeSplineMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}
