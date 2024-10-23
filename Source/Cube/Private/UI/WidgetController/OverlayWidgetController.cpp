// Copyright EderSantander developer


#include "UI/WidgetController/OverlayWidgetController.h"

#include "CubeGameplayTags.h"
#include "AbilitySystemComponent/CubeAbilitySystemComponent.h"
#include "AbilitySystemComponent/CubeAttributeSet.h"
#include "AbilitySystemComponent/Data/AttributeInformation.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/CubeHUD.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UCubeAttributeSet* CubeAttributeSet = CastChecked<UCubeAttributeSet>(AttributeSet);
	OnStaminaChangedDelegate.Broadcast(CubeAttributeSet->GetStamina());
	OnMaxStaminaChangedDelegate.Broadcast(CubeAttributeSet->GetMaxStamina());

	check(AttributeInformation);

	for (auto& Pair : CubeAttributeSet->TagsToAttributes)
	{
		BroadcastAttributeInformation(Pair.Key, Pair.Value());
	}
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const UCubeAttributeSet* CubeAttributeSet = CastChecked<UCubeAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CubeAttributeSet->GetStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CubeAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxStaminaChanged);
	
	Cast<UCubeAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTagsDelegate.AddLambda(
		[](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				UE_LOG(LogTemp, Warning, TEXT("TAG: [%s]"), *Tag.ToString());
			}
		});
	
	check(AttributeInformation);
	for (auto& Pair : CubeAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair, CubeAttributeSet](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInformation(Pair.Key, Pair.Value());
			}
		);
	}
}

FVector2D UOverlayWidgetController::GetWindowScreenSize()
{
	if (ACubeHUD* CubeHUD =  Cast<ACubeHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD()))
	{
		return  CubeHUD->HUDScreenSize();
	}
	return FVector2D::ZeroVector;
}

void UOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChangedDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::BroadcastAttributeInformation(const FGameplayTag& InAttributeTag, const FGameplayAttribute& InAttribute) const
{
	FUAttributeInformation Info = AttributeInformation->FindAttributeInfoByTag(InAttributeTag);
	Info.AttributeValue = InAttribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
