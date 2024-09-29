// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CubeCharacterBase.generated.h"

UCLASS(Abstract)
class CUBE_API ACubeCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACubeCharacterBase();
	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce) override;

	UPROPERTY(EditDefaultsOnly, Category="CubeMovement")
	float DistanceToMove = 100.f;
	
protected:
	virtual void BeginPlay() override;
};
