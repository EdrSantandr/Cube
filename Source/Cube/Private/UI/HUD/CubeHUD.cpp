// Copyright EderSantander developer


#include "UI/HUD/CubeHUD.h"
#include "UI/Widget/CubeUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ACubeHUD::GetOverlayWidgetController(const FWidgetControllerParams& WcParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WcParams);
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ACubeHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlaywidgetclass uninitialized"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlaywidgetControllerclass uninitialized"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UCubeUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams (PC, PS, Asc, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);

	Widget->AddToViewport();
}
