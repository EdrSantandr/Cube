// Copyright EderSantander developer


#include "Actor/CubeSplineMeshActor.h"
#include "Components/SplineComponent.h"

ACubeSplineMeshActor::ACubeSplineMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SetRootComponent(SplineComponent);
}

void ACubeSplineMeshActor::BeginPlay()
{
	Super::BeginPlay();

	if (AutoSpawn)
	{
		InteractionTimerDelegate.BindUObject(this, &ACubeSplineMeshActor::InteractionStart);
		GetWorld()->GetTimerManager().SetTimer(InteractionTimerHandle, InteractionTimerDelegate, StartInteractionTime, false);
	}
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

void ACubeSplineMeshActor::InteractionStart()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling InteractionStart"));
	if (BlockingClass)
	{
		const FTransform PointTransform = SplineComponent->GetTransformAtSplinePoint(0, ESplineCoordinateSpace::World);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnedActor = GetWorld()->SpawnActor<AActor>(BlockingClass, PointTransform, SpawnParameters);
		if (InteractionType == ESplineActorType::OneShot)
			MoveSpawnedBlockingOneShot();		
		if (InteractionType == ESplineActorType::Loop)
			MoveSpawnedBlockingLoop();
	}
	GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);
}

void ACubeSplineMeshActor::Destroyed()
{
	Super::Destroyed();
	GetWorld()->GetTimerManager().ClearTimer(InteractionTimerHandle);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}
