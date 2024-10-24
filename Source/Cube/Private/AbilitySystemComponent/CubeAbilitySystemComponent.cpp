// Copyright EderSantander developer


#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"

#include "AbilitySystemComponent/Abilities/CubeGameplayAbility.h"

void UCubeAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UCubeAbilitySystemComponent::EffectApplied);
}

void UCubeAbilitySystemComponent::SetupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, const float Level)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : InAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);
		if (const UCubeGameplayAbility* CubeGameplayAbility = Cast<UCubeGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(CubeGameplayAbility->InitialInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UCubeAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	
}

void UCubeAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
}

void UCubeAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
