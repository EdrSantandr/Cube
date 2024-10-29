// Copyright EderSantander developer


#include "Player/CubePlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"
#include "Input/CubeInputComponent.h"

ACubePlayerController::ACubePlayerController()
{
	bReplicates = true;
}

void ACubePlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(CubeContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
		Subsystem->AddMappingContext(CubeContext, 0);
	
	bShowMouseCursor = false;
}

void ACubePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UCubeInputComponent* CubeInputComponent = CastChecked<UCubeInputComponent>(InputComponent);
	CubeInputComponent->BindAbilityActions(CubeInputConfig,this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	if (IsValid(MoveAction))
	{
		CubeInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACubePlayerController::Move);	
	}
	if (IsValid(LookAction))
	{
		CubeInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACubePlayerController::LookAt);	
	}
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
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ACubePlayerController::LookAt(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACubePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//if (GetAsc() == nullptr) return;
	if (GetAsc() == nullptr) return;
	if (GetAsc()) GetAsc()->AbilityInputTagPressed(InputTag);
}

void ACubePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetAsc() == nullptr) return;
	if (GetAsc()) GetAsc()->AbilityInputTagReleased(InputTag);
}

void ACubePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetAsc() == nullptr) return;
	if (GetAsc()) GetAsc()->AbilityInputTagHeld(InputTag);
}

UCubeAbilitySystemComponent* ACubePlayerController::GetAsc()
{
	if (CubeAbilitySystemComponent == nullptr)
	{
		CubeAbilitySystemComponent = Cast<UCubeAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return CubeAbilitySystemComponent;
}
