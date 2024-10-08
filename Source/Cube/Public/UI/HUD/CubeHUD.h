// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CubeHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UCubeUserWidget;
/**
 * 
 */
UCLASS()
class CUBE_API ACubeHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UCubeUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WcParams);

	virtual void DrawHUD() override;	

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* Asc, UAttributeSet* AS);
	
	FVector2D HUDScreenSize() const;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCubeUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY()
	int32 ScreenHeight = 0;

	UPROPERTY()
	int32 ScreenWidth = 0;

	UPROPERTY()
	bool bSetScreenSize = false;
};
