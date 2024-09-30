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

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	FTimerHandle RotationTimerHandle;
	FTimerDelegate RotationDelegate;

	UFUNCTION()
	void FinishMovement(const FVector& InActorLocation);

private:
	bool bMeshRotation = false;
	FVector RotationDirection = FVector::ZeroVector;
	float ElapsedTimeRotation = 0.f;
	float SquareDiagonal = 0.f;
	float SquareExtend = 0.f;
	float InteractionTime = 0.f;
	float InitialHeight = 0.f;
	FVector InitialActorLocation = FVector::ZeroVector;
	
	UFUNCTION()
	void ControlHeight(float InDelta);

	UFUNCTION()
	void CalculateDiagonal();
};
