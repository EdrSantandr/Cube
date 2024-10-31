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

	UFUNCTION(BlueprintPure,Category="CubeSystemLibrary|GameplayMechanics")
	static TArray<FVector> EvenlySpreadVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors);

};
