// Copyright EderSantander developer


#include "AbilitySystemComponent/CubeAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "CubeGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


UCubeAttributeSet::UCubeAttributeSet()
{
	const FCubeGameplayTags& GameplayTags = FCubeGameplayTags::Get();

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Stamina, GetStaminaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_MaxStamina, GetMaxStaminaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_MovementTime, GetMovementTimeAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_JumpTime, GetJumpTimeAttribute);
}

void UCubeAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, MovementTime, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCubeAttributeSet, JumpTime, COND_None, REPNOTIFY_Always);
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

void UCubeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

}

void UCubeAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// SOURCE = causer of the effect, TARGET = target of the effect (owner of this Attribute Set)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceAsc = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceAsc) && Props.SourceAsc->AbilityActorInfo.IsValid() && Props.SourceAsc->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceAsc->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceAsc->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor!=nullptr )
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAsc =UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
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

void UCubeAttributeSet::OnRep_JumpTime(const FGameplayAttributeData& OldJumpTime) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCubeAttributeSet, JumpTime, OldJumpTime);
}

