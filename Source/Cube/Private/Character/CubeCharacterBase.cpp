// Copyright EderSantander developer


#include "Character/CubeCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

ACubeCharacterBase::ACubeCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UCubeAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UCubeAttributeSet>("AttributeSet");

	
}

void ACubeCharacterBase::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Jump"));
	Super::Jump();
}

UAbilitySystemComponent* ACubeCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACubeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void ACubeCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*
	if (bMeshRotation)
	{
		ElapsedTimeRotation += DeltaSeconds;
		ControlTranslation();
		ControlRotation(DeltaSeconds);
	}
	*/
}

void ACubeCharacterBase::CameraMovement(const FVector& NewLocation)
{
}

void ACubeCharacterBase::FinishMovement(const FVector& InActorLocation, const FRotator& InActorRotation)
{
	bMeshRotation = false;
	Translation = FVector::ZeroVector;
	TotalRotation = FRotator::ZeroRotator;
	ElapsedTimeRotation = 0.f;
	InteractionTime = 0.f;
	InitialHeight = 0.f;
	SetActorLocation(InActorLocation);
	CameraMovement(InActorLocation);
	SetActorRelativeRotation(InActorRotation);
	GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);
}

void ACubeCharacterBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UCubeAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	SetupAttributes();
	AddCharacterAbilities();
}

void ACubeCharacterBase::AddCharacterAbilities() const
{
	if (!HasAuthority()) return;
	if (UCubeAbilitySystemComponent* CubeAsc = Cast<UCubeAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		CubeAsc->SetupAbilities(InitialAbilities);	
	}
}

void ACubeCharacterBase::SetupAttributes() const
{
	ApplyEffectToSelf(DefaultMovementAttributes);
	ApplyEffectToSelf(SecondaryMovementAttributes);
}

void ACubeCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, const float InLevel) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(InGameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InGameplayEffectClass, InLevel, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ACubeCharacterBase::ControlTranslation()
{
	if (ElapsedTimeRotation < InteractionTime)
	{
		float DeltaZ = ElapsedTimeRotation/InteractionTime * DistanceToMove - SquareExtend;
		DeltaZ = FMath::Square(DeltaZ);
		DeltaZ = FMath::Square(SquareDiagonal) - DeltaZ;
		DeltaZ = FMath::Sqrt(DeltaZ) + InitialHeight;

		FVector DeltaTranslation = ElapsedTimeRotation/InteractionTime * Translation;
		DeltaTranslation = InitialActorLocation + DeltaTranslation;
		
		const FVector ActorDeltaLocation = FVector(DeltaTranslation.X, DeltaTranslation.Y, DeltaZ);
		CameraMovement(ActorDeltaLocation);
		SetActorLocation(ActorDeltaLocation);
	}
}

void ACubeCharacterBase::ControlRotation(float const InDelta)
{
	if (ElapsedTimeRotation < InteractionTime)
	{
		FVector DeltaRotation = FVector(90.f, 90.f,0.f) * ElapsedTimeRotation/InteractionTime;
		if (!FMath::IsNearlyZero(RotationDirection.X))
			DeltaRotation *= FVector(RotationDirection.X * -1.f,0.f , 0.f);
		if (!FMath::IsNearlyZero(RotationDirection.Y))
			DeltaRotation *= FVector(0.f, RotationDirection.Y , 0.f);
		TotalRotation = FRotator(DeltaRotation.X, 0.f,DeltaRotation.Y);
		SetActorRelativeRotation(TotalRotation);
	}
}

void ACubeCharacterBase::CalculateDiagonal()
{
	const FTransform LocalTransform;
	const FVector BoxExtend = GetMesh()->CalcBounds(LocalTransform).BoxExtent;
	SquareDiagonal = FMath::Sqrt(2.f)*BoxExtend.X;
	SquareExtend = BoxExtend.X;
	InitialHeight = 0.f;
}

bool ACubeCharacterBase::CanMoveNextLocation(const FVector& NextLocation) const
{
	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(OutHit, GetActorLocation(), NextLocation, ECC_Pawn,CollisionQueryParams);
	if (OutHit.bBlockingHit)
		return false;
	return true;	
}



