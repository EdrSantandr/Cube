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
	const FVector FinalLocation = GetActorLocation() + WorldDirection * ScaleValue * DistanceToMove;
	if (const UCubeAttributeSet* CubeAttributeSet = Cast<UCubeAttributeSet>(AttributeSet))
	{
		InteractionTime = CubeAttributeSet->MovementTime.GetCurrentValue();
		bMeshRotation = true;
		RotationDirection = WorldDirection;
		ElapsedTimeRotation = 0.f;
		//InitialHeight = GetMesh()->GetComponentLocation().Z;
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
		ControlHeight(DeltaSeconds);
		//Control Rotation
	}
}

void ACubeCharacterBase::FinishMovement(const FVector& InActorLocation)
{
	bMeshRotation = false;
	RotationDirection = FVector::ZeroVector;
	ElapsedTimeRotation = 0.f;
	InteractionTime = 0.f;
	InitialHeight = 0.f;
	DrawDebugSphere(GetWorld(), InActorLocation, 15.f, 12, FColor::Green, false, 5.f);
	SetActorLocation(InActorLocation);
	GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle);
}

void ACubeCharacterBase::ControlHeight(float InDelta)
{
	ElapsedTimeRotation += InDelta;
	if (ElapsedTimeRotation < InteractionTime)
	{
		float DeltaZ = ElapsedTimeRotation/InteractionTime * DistanceToMove - SquareExtend;
		DeltaZ = FMath::Square(DeltaZ);
		DeltaZ = FMath::Square(SquareDiagonal) - DeltaZ;
		UE_LOG(LogTemp, Warning, TEXT("first DeltaZ [%f]"), DeltaZ);
		DeltaZ = FMath::Sqrt(DeltaZ) + InitialHeight;
		UE_LOG(LogTemp, Warning, TEXT("After [%f]"), DeltaZ);
		
		const FVector ActorDeltaLocation = FVector(0.f,0.f, DeltaZ);
		SetActorLocation(ActorDeltaLocation);
	}
}

void ACubeCharacterBase::CalculateDiagonal()
{
	//getme
	FTransform LocalTransform;
	FVector BoxExtend = GetMesh()->CalcBounds(LocalTransform).BoxExtent;
	//UE_LOG(LogTemp, Warning, TEXT("Box extend [%s]"),*BoxExtend.ToString());
	//This is only because it's a square 
	SquareDiagonal = FMath::Sqrt(2.f)*BoxExtend.X;
	UE_LOG(LogTemp, Warning, TEXT("Diagonal [%f]"), SquareDiagonal);
	SquareExtend = BoxExtend.X;
	InitialHeight = 0.f;
}



