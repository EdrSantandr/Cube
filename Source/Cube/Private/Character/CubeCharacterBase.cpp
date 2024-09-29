// Copyright EderSantander developer


#include "Character/CubeCharacterBase.h"

ACubeCharacterBase::ACubeCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACubeCharacterBase::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	SetActorLocation(GetActorLocation() + WorldDirection * ScaleValue * DistanceToMove);
}

void ACubeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}


