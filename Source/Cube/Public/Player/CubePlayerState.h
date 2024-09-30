// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "CubePlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class CUBE_API ACubePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACubePlayerState();
};
