// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CubeGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API UCubeGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag InitialInputTag;
	
};
