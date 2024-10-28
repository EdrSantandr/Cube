// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent/Abilities/CubeGameplayAbility.h"
#include "MovementGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API UMovementGameplayAbility : public UCubeGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="PawnMovement")
	void MovePawn(const FVector Direction, const float Scale);

	UFUNCTION(BlueprintCallable, Category="PawnMovement")
	void MoveJump();
};
