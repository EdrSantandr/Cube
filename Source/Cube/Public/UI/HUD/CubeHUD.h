// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CubeHUD.generated.h"

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

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCubeUserWidget> OverlayWidgetClass;
	
};
