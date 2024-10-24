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

void ACubePlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetAsc() == nullptr) return;
}

void ACubePlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetAsc() == nullptr) return;
	GetAsc()->AbilityInputTagReleased(InputTag);
}

void ACubePlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetAsc() == nullptr) return;
	GetAsc()->AbilityInputTagHeld(InputTag);
}

UCubeAbilitySystemComponent* ACubePlayerController::GetAsc()
{
	if (CubeAbilitySystemComponent == nullptr)
	{
		CubeAbilitySystemComponent = Cast<UCubeAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return CubeAbilitySystemComponent;
}
