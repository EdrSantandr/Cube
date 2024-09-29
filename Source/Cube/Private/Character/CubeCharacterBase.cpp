// Copyright EderSantander developer


#include "Character/CubeCharacterBase.h"

// Sets default values
ACubeCharacterBase::ACubeCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACubeCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

