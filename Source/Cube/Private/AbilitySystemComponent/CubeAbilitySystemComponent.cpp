// Copyright EderSantander developer


#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"

void UCubeAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UCubeAbilitySystemComponent::EffectApplied);
}

void UCubeAbilitySystemComponent::SetupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, const float Level)
{
	for (auto AbilityClass : InAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);
		GiveAbility(AbilitySpec);
	}
}

void UCubeAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTagsDelegate.Broadcast(TagContainer);
}
