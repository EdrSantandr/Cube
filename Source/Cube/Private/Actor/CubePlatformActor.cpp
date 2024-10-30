// Copyright EderSantander developer


#include "Actor/CubePlatformActor.h"

#include "Components/BoxComponent.h"
#include "GameFramework/MovementComponent.h"

ACubePlatformActor::ACubePlatformActor()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	SetRootComponent(MeshComponent);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxComponent->SetupAttachment(GetRootComponent());

	MovementComponent = CreateDefaultSubobject<UMovementComponent>("MovementComponent");
}

void ACubePlatformActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACubePlatformActor::OnBeginOverlap);
}

void ACubePlatformActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	WarningDelegate.BindUFunction(this, "Warning_Elapsed");
	GetWorld()->GetTimerManager().SetTimer(WarningTimerHandle,WarningDelegate, WarningTime, false);
	MaterialEffect();
}

void ACubePlatformActor::Warning_Elapsed() const
{
	MeshComponent->SetSimulatePhysics(true);
}

