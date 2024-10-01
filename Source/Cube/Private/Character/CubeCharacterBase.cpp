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
		RotationDelegate.BindUFunction(this,"FinishMovement", FinalLocation);
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
		//Control Z height
		ElapsedTimeRotation += DeltaSeconds;
		ControlTranslation();
		//Control Rotation
		ControlRotation(DeltaSeconds);
	}
}

void ACubeCharacterBase::FinishMovement(const FVector& InActorLocation)
{
	//todo: attach camera and spring arm component
	bMeshRotation = false;
	Translation = FVector::ZeroVector;
	TotalRotation = FRotator::ZeroRotator;
	ElapsedTimeRotation = 0.f;
	InteractionTime = 0.f;
	InitialHeight = 0.f;
	
	DrawDebugSphere(GetWorld(), InActorLocation, 15.f, 12, FColor::Green, false, 5.f);
	SetActorLocation(InActorLocation);
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

		FVector DeltaTraslation = ElapsedTimeRotation/InteractionTime * Translation;
		DeltaTraslation = InitialActorLocation + DeltaTraslation;
		
		const FVector ActorDeltaLocation = FVector(DeltaTraslation.X, DeltaTraslation.Y, DeltaZ);
		SetActorLocation(ActorDeltaLocation);
	}
}

void ACubeCharacterBase::ControlRotation(float const InDelta)
{
	if (ElapsedTimeRotation < InteractionTime)
	{
		FVector DeltaRotation = FVector(90.f, 90.f,0.f) * ElapsedTimeRotation/InteractionTime;
		if (!FMath::IsNearlyZero(RotationDirection.X))
		{
			DeltaRotation *= FVector(RotationDirection.X * -1.f,0.f , 0.f);
			UE_LOG(LogTemp, Warning, TEXT("DELTA X rotation [%s]"), *DeltaRotation.ToString());
		}
		if (!FMath::IsNearlyZero(RotationDirection.Y))
		{
			DeltaRotation *= FVector(0.f, RotationDirection.Y * -1.f, 0.f);
			UE_LOG(LogTemp, Warning, TEXT("DELTA Y rotation [%s]"), *DeltaRotation.ToString());
		}
		
		TotalRotation = FRotator(DeltaRotation.X, DeltaRotation.Y,0.f);
		UE_LOG(LogTemp, Warning, TEXT("rotation [%s]"), *TotalRotation.ToString());
		//SetActorRotation(DeltaRotation.Rotation(), ETeleportType::None);
		SetActorRelativeRotation(TotalRotation);
	}
}

void ACubeCharacterBase::CalculateDiagonal()
{
	FTransform LocalTransform;
	FVector BoxExtend = GetMesh()->CalcBounds(LocalTransform).BoxExtent;
	//This is only because it's a square 
	SquareDiagonal = FMath::Sqrt(2.f)*BoxExtend.X;
	SquareExtend = BoxExtend.X;
	InitialHeight = 0.f;
}



