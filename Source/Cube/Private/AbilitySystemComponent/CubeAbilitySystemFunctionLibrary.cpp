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

TArray<FVector> UCubeAbilitySystemFunctionLibrary::EvenlySpreadVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors)
{
	TArray<FVector> Vectors;
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-Spread/2.f, Axis);
	if (NumVectors>1)
	{
		const float DeltaSpread = Spread / (NumVectors-1);
		for(int32 i=0; i<NumVectors;i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread*i, Axis);
			Vectors.Add(Direction);
		}
	}
	else
	{
		Vectors.Add(Forward);
	}
	return Vectors;
}
