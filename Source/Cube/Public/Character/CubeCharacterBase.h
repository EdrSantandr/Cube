// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CubeCharacterBase.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class CUBE_API ACubeCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACubeCharacterBase();
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) override;

	UPROPERTY(EditDefaultsOnly, Category="CubeMovement")
	float DistanceToMove = 100.f;

	/*Ability system Interface*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
