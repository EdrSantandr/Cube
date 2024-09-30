// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CubeAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class CUBE_API UCubeAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UCubeAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*Current stamina you will use for each special movement*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "MovementAttributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCubeAttributeSet, Stamina);

	/*Max stamina available*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "MovementAttributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCubeAttributeSet, MaxStamina);

	/* Movement time duration*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementTime, Category = "MovementAttributes")
	FGameplayAttributeData MovementTime;
	ATTRIBUTE_ACCESSORS(UCubeAttributeSet, MovementTime);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

	UFUNCTION()
	void OnRep_MovementTime(const FGameplayAttributeData& OldMovementTime) const;
};
