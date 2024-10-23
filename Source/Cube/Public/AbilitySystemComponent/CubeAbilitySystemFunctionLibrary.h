// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CubeAbilitySystemFunctionLibrary.generated.h"

class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class CUBE_API UCubeAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="CubeSystemLibrary|WidgetController", meta=(DefaultToSelf="InWorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* InWorldContextObject);
};
