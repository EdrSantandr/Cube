// Copyright EderSantander developer


#include "AbilitySystemComponent/Abilities/MovementGameplayAbility.h"

#include "GameFramework/Character.h"

void UMovementGameplayAbility::MovePawn(const FVector Direction, const float Scale)
{
	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
	{
		Character->AddMovementInput(Direction, Scale);
	}
}

void UMovementGameplayAbility::MoveJump()
{
	if (ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo()))
	{
		Character->Jump();
	}
}
