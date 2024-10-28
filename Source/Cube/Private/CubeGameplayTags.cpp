// Copyright EderSantander developer


#include "CubeGameplayTags.h"
#include "GameplayTagsManager.h"

FCubeGameplayTags FCubeGameplayTags::CubeGameplayTags;

void FCubeGameplayTags::InitializeGameplayTags()
{
	/************************************ ABILITITIES COOLDOWN ***********************/ 
	CubeGameplayTags.Cooldown_Movement_Backward = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Movement.Backward"),
		FString("Cooldown.Movement.Backward for character"));

	CubeGameplayTags.Cooldown_Movement_Forward = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Movement.Forward"),
		FString("Cooldown.Movement.Forward for character"));

	CubeGameplayTags.Cooldown_Movement_Left = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Movement.Left"),
		FString("Cooldown.Movement.Left for character"));

	CubeGameplayTags.Cooldown_Movement_Right = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Movement.Right"),
		FString("Cooldown.Movement.Right for character"));

	CubeGameplayTags.Cooldown_Movement_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Movement.Jump"),
		FString("Cooldown.Movement.Jump for character"));
	
	/************************************ ABILITIES ***********************/ 
	CubeGameplayTags.Abilities_Movement_Backward = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Movement.Backward"),
		FString("Abilities.Movement.Backward for character"));

	CubeGameplayTags.Abilities_Movement_Forward = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Movement.Forward"),
		FString("Abilities.Movement.Forward for character"));

	CubeGameplayTags.Abilities_Movement_Left = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Movement.Left"),
		FString("Abilities.Movement.Left for character"));

	CubeGameplayTags.Abilities_Movement_Right = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Movement.Right"),
		FString("Abilities.Movement.Right for character"));

	CubeGameplayTags.Abilities_Movement_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Movement.Jump"),
			FString("Abilities.Movement.Jump for character"));
	
	/************************************ PRIMARY ATTRIBUTES ***********************/ 
	CubeGameplayTags.Attributes_Primary_MovementTime = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MovementTime"),
		FString("movement time from character"));

	CubeGameplayTags.Attributes_Primary_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Stamina"),
		FString("stamina used by the character"));

	CubeGameplayTags.Attributes_Primary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MaxStamina"),
		FString("max stamina allowed for the character"));

	/************************************ SECONDARY ATTRIBUTES ***********************/
	CubeGameplayTags.Attributes_Secondary_JumpTime = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.JumpTime"),
		FString("Attributes.Secondary for jump time for character"));

	/************************************ INPUT MOVEMENT ***********************/
	CubeGameplayTags.Input_Movement_Backward = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Movement.Backward"),
		FString("Input.Movement.Backward for player input"));

	CubeGameplayTags.Input_Movement_Forward = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Movement.Forward"),
		FString("Input.Movement.Forward for player input"));

	CubeGameplayTags.Input_Movement_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Movement.Jump"),
		FString("Input.Movement.Jump for player input"));

	CubeGameplayTags.Input_Movement_Left = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Movement.Left"),
		FString("Input.Movement.Left for player input"));

	CubeGameplayTags.Input_Movement_Right = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Movement.Right"),
		FString("Input.Movement.Right for player input"));
}
