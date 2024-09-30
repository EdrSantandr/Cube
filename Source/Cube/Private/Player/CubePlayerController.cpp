// Copyright EderSantander developer


#include "Player/CubePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ACubePlayerController::ACubePlayerController()
{
	bReplicates = true;
}

void ACubePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(CubeContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(CubeContext, 0);
	bShowMouseCursor = false;
}

void ACubePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACubePlayerController::Move);
}

void ACubePlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (!FMath::IsNearlyZero(InputAxisVector.Y))
			ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y, true);

		if (!FMath::IsNearlyZero(InputAxisVector.X))
			ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X, true);
	}
}
