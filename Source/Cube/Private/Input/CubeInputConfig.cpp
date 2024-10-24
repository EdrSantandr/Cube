// Copyright EderSantander developer


#include "Input/CubeInputConfig.h"

const UInputAction* UCubeInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InInputTag, bool bLogNotFound)
{
	for (const FCubeInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InInputTag))
			return Action.InputAction; 
	}

	if (!bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("cant find ability with tag [%s]"), *InInputTag.ToString());
	}
	return nullptr;
}
