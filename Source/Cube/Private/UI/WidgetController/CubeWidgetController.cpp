// Copyright EderSantander developer


#include "UI/WidgetController/CubeWidgetController.h"

void UCubeWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WcParams)
{
	PlayerController = WcParams.PlayerController;
	PlayerState = WcParams.PlayerState;
	AbilitySystemComponent = WcParams.AbilitySystemComponent;
	AttributeSet = WcParams.AttributeSet;
}

void UCubeWidgetController::BroadcastInitialValues()
{
}
