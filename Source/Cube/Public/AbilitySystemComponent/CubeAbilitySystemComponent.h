// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CubeAbilitySystemComponent.generated.h"
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSignature, const FGameplayTagContainer &);

/**
 * 
 */
UCLASS()
class CUBE_API UCubeAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	FEffectAssetTagsSignature EffectAssetTagsDelegate;

	UFUNCTION()
	void SetupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, const float Level = 1.f);
	
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
