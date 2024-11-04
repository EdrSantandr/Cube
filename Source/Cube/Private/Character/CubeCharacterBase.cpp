// Copyright EderSantander developer


#include "Character/CubeCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAttributeSet.h"

ACubeCharacterBase::ACubeCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UCubeAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UCubeAttributeSet>("AttributeSet");
}

void ACubeCharacterBase::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Jump"));
	Super::Jump();
}

UAbilitySystemComponent* ACubeCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACubeCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void ACubeCharacterBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UCubeAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	SetupAttributes();
	AddCharacterAbilities();
}

void ACubeCharacterBase::AddCharacterAbilities() const
{
	if (!HasAuthority()) return;
	if (UCubeAbilitySystemComponent* CubeAsc = Cast<UCubeAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		CubeAsc->SetupAbilities(InitialAbilities);	
	}
}

void ACubeCharacterBase::SetupAttributes() const
{
	ApplyEffectToSelf(DefaultMovementAttributes);
	ApplyEffectToSelf(SecondaryMovementAttributes);
}

void ACubeCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, const float InLevel) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(InGameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InGameplayEffectClass, InLevel, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}
