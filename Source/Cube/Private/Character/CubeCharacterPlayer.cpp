// Copyright EderSantander developer


#include "Character/CubeCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CubePlayerController.h"
#include "Player/CubePlayerState.h"
#include "UI/HUD/CubeHUD.h"

ACubeCharacterPlayer::ACubeCharacterPlayer()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
}

void ACubeCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitActorInfo();
}

void ACubeCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SpringArmComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	InitialCameraPosition = CameraComponent->GetComponentLocation();
}

void ACubeCharacterPlayer::CameraMovement(const FVector& NewLocation)
{
	FVector CameraLocation = InitialCameraPosition;
	if (!FMath::IsNearlyZero(NewLocation.X))
		CameraLocation.X += NewLocation.X;
	if (!FMath::IsNearlyZero(NewLocation.Y))
		CameraLocation.Y += NewLocation.Y;
	/* todo: Uncomment this one if you like camera moving on Z Axis
	if (!FMath::IsNearlyZero(NewLocation.Z))
		CameraLocation.Z += NewLocation.Z;
	*/
	CameraComponent->SetWorldLocation(CameraLocation);
}

void ACubeCharacterPlayer::InitActorInfo() const
{
	ACubePlayerState* CubePlayerState =GetPlayerState<ACubePlayerState>();
	check(CubePlayerState);
	
	if (ACubePlayerController* CubePlayerController = Cast<ACubePlayerController>(GetController()))
	{
		if (ACubeHUD* CubeHUD = Cast<ACubeHUD>(CubePlayerController->GetHUD()))
		{
			CubeHUD->InitOverlay(CubePlayerController, CubePlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
