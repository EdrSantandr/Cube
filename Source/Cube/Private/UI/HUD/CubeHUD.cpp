// Copyright EderSantander developer


#include "UI/HUD/CubeHUD.h"
#include "UI/Widget/CubeUserWidget.h"

void ACubeHUD::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
