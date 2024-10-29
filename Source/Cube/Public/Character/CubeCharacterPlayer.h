// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "Character/CubeCharacterBase.h"
#include "CubeCharacterPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class CUBE_API ACubeCharacterPlayer : public ACubeCharacterBase
{
	GENERATED_BODY()

public:
	ACubeCharacterPlayer();

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditDefaultsOnly, Category="CubeCamera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category="CubeCamera")
	TObjectPtr<UCameraComponent> CameraComponent;

protected:
	void InitActorInfo() const;
};
