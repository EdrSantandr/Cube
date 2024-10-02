// Copyright EderSantander developer


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystemComponent/CubeAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UCubeAttributeSet* CubeAttributeSet = CastChecked<UCubeAttributeSet>(AttributeSet);
	OnStaminaChangedDelegate.Broadcast(CubeAttributeSet->GetStamina());
	OnMaxStaminaChangedDelegate.Broadcast(CubeAttributeSet->GetMaxStamina());
}
