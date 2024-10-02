// Copyright EderSantander developer


#include "UI/Widget/CubeUserWidget.h"

void UCubeUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController =InWidgetController;
	WidgetControllerSet();
}
