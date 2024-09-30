// Copyright EderSantander developer


#include "Character/CubeCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAttributeSet.h"

ACubeCharacterBase::ACubeCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = CreateDefaultSubobject<UCubeAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UCubeAttributeSet>("AttributeSet");
}

void ACubeCharacterBase::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	//SetActorLocation(GetActorLocation() + WorldDirection * ScaleValue * DistanceToMove);
	const FVector ActorLocation = GetActorLocation();
	DrawDebugSphere(GetWorld(), ActorLocation, 15.f, 12, FColor::Blue, false, 5.f);
	const FVector FinalLocation = ActorLocation + WorldDirection * ScaleValue * DistanceToMove;
	DrawDebugSphere(GetWorld(), FinalLocation, 15.f, 12, FColor::Red, false, 5.f);
	// Get the movement time attribute
	if (const UCubeAttributeSet* CubeAttributeSet = Cast<UCubeAttributeSet>(AttributeSet))
	{
		const float MovementTime = CubeAttributeSet->MovementTime.GetCurrentValue();
		//RotationDelegate.BindUObject(this,&ACubeCharacterBase::FinishMovement, FinalLocation);
		RotationDelegate.BindUFunction(this,"FinishMovement", FinalLocation);
		GetWorld()->GetTimerManager().SetTimer(RotationTimerHandle, RotationDelegate, MovementTime, false);
	}
}

UAbilitySystemComponent* ACubeCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACubeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ACubeCharacterBase::FinishMovement(const FVector& InActorLocation)
{
	DrawDebugSphere(GetWorld(), InActorLocation, 15.f, 12, FColor::Green, false, 5.f);
	SetActorLocation(InActorLocation);
	GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);
}



