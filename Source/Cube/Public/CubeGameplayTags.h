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
protected:
private:
	static FCubeGameplayTags CubeGameplayTags;
};
