// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * SINGLETON
 */

struct FCubeGameplayTags
{
public:
	static const FCubeGameplayTags& Get() { return CubeGameplayTags;}
	static void InitializeGameplayTags();

	// Abilities
	FGameplayTag Cooldown_Movement_Left;
	FGameplayTag Cooldown_Movement_Right;
	FGameplayTag Cooldown_Movement_Forward;
	FGameplayTag Cooldown_Movement_Backward;
	FGameplayTag Cooldown_Movement_Jump;
	
	// Abilities
	FGameplayTag Abilities_Movement_Left;
	FGameplayTag Abilities_Movement_Right;
	FGameplayTag Abilities_Movement_Forward;
	FGameplayTag Abilities_Movement_Backward;
	FGameplayTag Abilities_Movement_Jump;
	
	// Primary Attributes
	FGameplayTag Attributes_Primary_MovementTime;
	FGameplayTag Attributes_Primary_Stamina;
	FGameplayTag Attributes_Primary_MaxStamina;

	// Secondary Attributes
	FGameplayTag Attributes_Secondary_JumpTime;
	
	// Input
	FGameplayTag Input_Movement_Forward;
	FGameplayTag Input_Movement_Backward;
	FGameplayTag Input_Movement_Right;
	FGameplayTag Input_Movement_Left;
	FGameplayTag Input_Movement_Jump;

private:
	static FCubeGameplayTags CubeGameplayTags;
};
