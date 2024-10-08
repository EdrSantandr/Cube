// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CubeUserWidget.generated.h"

UENUM(BlueprintType)
enum class EPlatformSupported : uint8
{
	Windows,
	Android
};

/**
 * 
 */
UCLASS()
class CUBE_API UCubeUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
