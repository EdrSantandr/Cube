// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "CubePlayerController.generated.h"
class UCubeAbilitySystemComponent;
class UCubeInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class CUBE_API ACubePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACubePlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="CubeInput")
	TObjectPtr<UInputMappingContext> CubeContext;

	void Move(const FInputActionValue& InputActionValue);

	void Jump(const FInputActionValue& InputActionValue);
	
	UFUNCTION(BlueprintCallable, Category="CubeInput")
	void AbilityInputTagPressed(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable, Category="CubeInput")
	void AbilityInputTagReleased(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable, Category="CubeInput")
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category="CubeInput")
	TObjectPtr<UCubeInputConfig> CubeInputConfig;

	UPROPERTY(EditDefaultsOnly, Category="CubeInput")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="CubeInput")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY()
	TObjectPtr<UCubeAbilitySystemComponent> CubeAbilitySystemComponent = nullptr;

	UCubeAbilitySystemComponent* GetAsc();
};
