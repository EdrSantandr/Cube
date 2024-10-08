// Copyright EderSantander developer


#include "Actor/CubeEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
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
	switch (EffectType)
	{
		case EAppliedAbilityEffectType::Instant:
			ApplyEffectToTarget(OtherActor, InstantGameplayEffect);	
			break;
		case EAppliedAbilityEffectType::Duration:
			ApplyEffectToTarget(OtherActor, DurationGameplayEffect);	
			break;
		case EAppliedAbilityEffectType::Infinite:
			ApplyEffectToTarget(OtherActor, InfiniteGameplayEffect);	
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("No effect applied"));		
	}
	Destroy();
}

void ACubeEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("END OVERLAP"));
}

void ACubeEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target))
	{
		check(GameplayEffectClass);
		FGameplayEffectContextHandle EffectContextHandle = TargetAsc->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		//todo: level should be set
		FGameplayEffectSpecHandle EffectSpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
		TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
