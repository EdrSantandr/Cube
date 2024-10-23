// Copyright EderSantander developer


#include "AbilitySystemComponent/Data/AttributeInformation.h"

FUAttributeInformation UAttributeInformation::FindAttributeInfoByTag(const FGameplayTag& InAttributeTag, bool bLogNotFound)
{
	for (const FUAttributeInformation& Information : AttributeInformation)
	{
		if (Information.AttributeTag.MatchesTagExact(InAttributeTag))
			return Information;
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("can't find attribute tag [%s]"), *InAttributeTag.ToString());
	}
	return FUAttributeInformation();
}
