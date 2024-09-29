// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CubeAttributeSet.generated.h"

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

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "MovementAttributes")
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "MovementAttributes")
	FGameplayAttributeData MaxStamina;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;
};
