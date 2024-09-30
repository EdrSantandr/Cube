// Copyright EderSantander developer


#include "AbilitySystemComponent/CubeAttributeSet.h"
#include "Net/UnrealNetwork.h"


UCubeAttributeSet::UCubeAttributeSet()
{
	InitStamina(100.f);
	InitMaxStamina(100.f);
	InitMovementTime(2.f);
}

void UCubeAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, MovementTime, COND_None, REPNOTIFY_Always);
}

void UCubeAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCubeAttributeSet, Stamina, OldStamina);
}

void UCubeAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCubeAttributeSet, MaxStamina, OldMaxStamina);
}

void UCubeAttributeSet::OnRep_MovementTime(const FGameplayAttributeData& OldMovementTime) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCubeAttributeSet, MovementTime, OldMovementTime);
}

