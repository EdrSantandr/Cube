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
	OnActorBeginOverlap(OtherActor);
}

void ACubeEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("END OVERLAP"));
	OnActorEndOverlap(OtherActor);
}

void ACubeEffectActor::OnActorBeginOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectCustomApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffect);
	}
	if (DurationApplicationPolicy == EEffectCustomApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect);
	}
	if (InfiniteApplicationPolicy == EEffectCustomApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect);
	}
}

void ACubeEffectActor::OnActorEndOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectCustomApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffect);
	}
	if (DurationApplicationPolicy == EEffectCustomApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect);
	}
	if (InfiniteApplicationPolicy == EEffectCustomApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect);
	}
	if (InfiniteRemovalPolicy == EEffectCustomRemovalPolicy::RemoveOnEndOverlap)
	{
		if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
		{
			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
			{
				if (TargetAsc == HandlePair.Value)
				{
					TargetAsc->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
			for(FActiveGameplayEffectHandle& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
	if (bRemoveActorOnEndOverlap)
	{
		Destroy();
	}
}

void ACubeEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target))
	{
		check(GameplayEffectClass);
		FGameplayEffectContextHandle EffectContextHandle = TargetAsc->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetAsc->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetAsc->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
		if (bIsInfinite && InfiniteRemovalPolicy == EEffectCustomRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveGameplayEffectHandle, TargetAsc);
		}	
	}
}
