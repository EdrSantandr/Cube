// Copyright EderSantander developer


#include "UI/HUD/CubeHUD.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Widget/CubeUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ACubeHUD::GetOverlayWidgetController(const FWidgetControllerParams& WcParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WcParams);
		OverlayWidgetController->BindCallbackToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ACubeHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!bSetScreenSize)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(ScreenWidth, ScreenHeight);
		UE_LOG(LogTemp, Warning, TEXT("sCREEN SIZE width [%i] heigth [%i]"), ScreenWidth, ScreenHeight);
		bSetScreenSize = true;
	}
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
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

FVector2D ACubeHUD::HUDScreenSize() const
{
	return FVector2D(ScreenWidth, ScreenHeight);
}
