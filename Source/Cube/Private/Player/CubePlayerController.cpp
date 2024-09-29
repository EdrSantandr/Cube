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
		UE_LOG(LogTemp, Warning, TEXT("FORWARD direction [%s] inputaxisvector Y [%f]"),*ForwardDirection.ToString(), InputAxisVector.Y);
		UE_LOG(LogTemp, Warning, TEXT("RIGHT direction [%s] inputaxisvector X [%f]"),*RightDirection.ToString(), InputAxisVector.X);
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
