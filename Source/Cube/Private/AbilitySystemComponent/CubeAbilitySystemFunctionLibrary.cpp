// Copyright EderSantander developer


#include "AbilitySystemComponent/CubeAbilitySystemFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "Character/CubeCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CubePlayerState.h"
#include "UI/HUD/CubeHUD.h"
#include "UI/WidgetController/CubeWidgetController.h"

UOverlayWidgetController* UCubeAbilitySystemFunctionLibrary::GetOverlayWidgetController(const UObject* InWorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(InWorldContextObject,0))
	{
		if (ACubeHUD* CubeHUD = Cast<ACubeHUD>(PlayerController->GetHUD()))
		{
			ACubePlayerState* CubePlayerState =  PlayerController->GetPlayerState<ACubePlayerState>();
			
			if (const ACubeCharacterBase* CubeCharacterBase = Cast<ACubeCharacterBase>(PlayerController->GetCharacter()))
			{
				if (UAbilitySystemComponent* AbilitySystemComponent = CubeCharacterBase->GetAbilitySystemComponent())
				{
					if (UAttributeSet* AttributeSet = CubeCharacterBase->GetAttributeSet())
					{
						const FWidgetControllerParams WidgetControllerParams(PlayerController, CubePlayerState, AbilitySystemComponent, AttributeSet);
						return CubeHUD->GetOverlayWidgetController(WidgetControllerParams);
					}
				}
			} 
		}
	}
	return nullptr;
}
