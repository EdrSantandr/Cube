// Copyright EderSantander developer


#include "Actor/CubeEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent/CubeAttributeSet.h"
#include "Components/BoxComponent.h"

ACubeEffectActor::ACubeEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	SetRootComponent(MeshComponent);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxComponent->SetupAttachment(GetRootComponent());
}

void ACubeEffectActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACubeEffectActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACubeEffectActor::OnEndOverlap);
}

void ACubeEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BEGIN OVERLAP"));
	if (IAbilitySystemInterface* AscInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UCubeAttributeSet* CubeAttributeSet = Cast<UCubeAttributeSet>(AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UCubeAttributeSet::StaticClass()));
		UCubeAttributeSet* MutableAttributeSet = const_cast<UCubeAttributeSet*>(CubeAttributeSet);
		//MutableAttributeSet->SetMovementTime(CubeAttributeSet->GetMovementTime() - 0.2f);
		MutableAttributeSet->SetStamina(CubeAttributeSet->GetStamina() + 25.f);
		Destroy();
	}
}

void ACubeEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("END OVERLAP"));
}
