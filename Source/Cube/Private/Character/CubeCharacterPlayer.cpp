// Copyright EderSantander developer


#include "Character/CubeCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACubeCharacterPlayer::ACubeCharacterPlayer()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void ACubeCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SpringArmComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}
