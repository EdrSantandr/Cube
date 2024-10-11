// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/CubeWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CUBE_API UOverlayWidgetController : public UCubeWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnStaminaChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxStaminaChangedDelegate;

	UFUNCTION(BlueprintCallable, Category="ScreenSize")
	FVector2D GetWindowScreenSize();

protected:
	void StaminaChanged(const FOnAttributeChangeData& Data) const;
	void MaxStaminaChanged(const FOnAttributeChangeData& Data) const;
};
