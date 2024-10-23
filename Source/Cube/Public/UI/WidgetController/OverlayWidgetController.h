// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/CubeWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAttributeInformation;
struct FUAttributeInformation;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FUAttributeInformation&, Information);
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

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInformation> AttributeInformation;
	
};
