// Copyright EderSantander developer


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystemComponent/CubeAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/CubeHUD.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UCubeAttributeSet* CubeAttributeSet = CastChecked<UCubeAttributeSet>(AttributeSet);
	OnStaminaChangedDelegate.Broadcast(CubeAttributeSet->GetStamina());
	OnMaxStaminaChangedDelegate.Broadcast(CubeAttributeSet->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const UCubeAttributeSet* CubeAttributeSet = CastChecked<UCubeAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CubeAttributeSet->GetStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::StaminaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CubeAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxStaminaChanged);
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
