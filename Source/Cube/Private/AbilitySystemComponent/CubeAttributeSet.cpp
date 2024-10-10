// Copyright EderSantander developer


#include "AbilitySystemComponent/CubeAttributeSet.h"
#include "Net/UnrealNetwork.h"


UCubeAttributeSet::UCubeAttributeSet()
{
	InitStamina(50.f);
	InitMaxStamina(100.f);
	InitMovementTime(0.5f);
}

void UCubeAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, MovementTime, COND_None, REPNOTIFY_Always);
}

void UCubeAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f, GetMaxStamina());
	}
	if (Attribute == GetMovementTimeAttribute())
	{
		NewValue = FMath::Max(NewValue,0.01f);
	}
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

