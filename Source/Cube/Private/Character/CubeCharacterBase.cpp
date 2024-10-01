// Copyright EderSantander developer


#include "Character/CubeCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAttributeSet.h"

ACubeCharacterBase::ACubeCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UCubeAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UCubeAttributeSet>("AttributeSet");
}

void ACubeCharacterBase::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	RotationDirection = WorldDirection * ScaleValue;
	Translation = WorldDirection * ScaleValue * DistanceToMove;
	InitialActorLocation = GetActorLocation();
	const FVector FinalLocation = InitialActorLocation + Translation;
	if (const UCubeAttributeSet* CubeAttributeSet = Cast<UCubeAttributeSet>(AttributeSet))
	{
		InteractionTime = CubeAttributeSet->MovementTime.GetCurrentValue();
		bMeshRotation = true;
		ElapsedTimeRotation = 0.f;
		CalculateDiagonal();
		FVector ConstantRotation = FVector(1.f,1.f,1.f) * 90.f;
		ConstantRotation *= WorldDirection;
		FRotator FinalRotation = FRotator(ConstantRotation.X, 0.f,ConstantRotation.Y);
		RotationDelegate.BindUFunction(this,"FinishMovement", FinalLocation, FinalRotation);
		GetWorld()->GetTimerManager().SetTimer(RotationTimerHandle, RotationDelegate, InteractionTime, false);
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

void ACubeCharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bMeshRotation)
	{
		ElapsedTimeRotation += DeltaSeconds;
		ControlTranslation();
		ControlRotation(DeltaSeconds);
	}
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



