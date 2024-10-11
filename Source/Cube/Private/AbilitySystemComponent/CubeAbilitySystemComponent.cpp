// Copyright EderSantander developer


#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"

void UCubeAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UCubeAbilitySystemComponent::EffectApplied);
}

void UCubeAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		//todo: broadcast tag to widget controller
		UE_LOG(LogTemp, Warning, TEXT("TAG: [%s]"), *Tag.ToString());
	}
}
