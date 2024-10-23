// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CubeCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
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

	virtual void CameraMovement(const FVector& NewLocation);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultMovementAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> SecondaryMovementAttributes;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	FTimerHandle RotationTimerHandle;
	FTimerDelegate RotationDelegate;

	UFUNCTION()
	void FinishMovement(const FVector& InActorLocation, const FRotator& InActorRotation);

	UFUNCTION()
	void InitAbilityActorInfo();

	UFUNCTION()
	void AddCharacterAbilities() const;

private:
	UFUNCTION()
	void SetupAttributes() const;

	UFUNCTION()
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, float InLevel = 1.f) const;
	
	bool bMeshRotation = false;
	FVector Translation = FVector::ZeroVector;
	float ElapsedTimeRotation = 0.f;
	float SquareDiagonal = 0.f;
	float SquareExtend = 0.f;
	float InteractionTime = 0.f;
	float InitialHeight = 0.f;
	FVector InitialActorLocation = FVector::ZeroVector;
	FVector RotationDirection = FVector::ZeroVector;
	FRotator TotalRotation = FRotator::ZeroRotator;
	
	UFUNCTION()
	void ControlTranslation();

	UFUNCTION()
	void ControlRotation(float const InDelta);

	UFUNCTION()
	void CalculateDiagonal();

	UFUNCTION()
	bool CanMoveNextLocation(const FVector& NextLocation) const;

	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;
};
