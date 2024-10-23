// Copyright EderSantander developer


#include "CubeGameplayTags.h"
#include "GameplayTagsManager.h"

FCubeGameplayTags FCubeGameplayTags::CubeGameplayTags;

void FCubeGameplayTags::InitializeGameplayTags()
{
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
