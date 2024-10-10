// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CubeAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API UCubeAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
