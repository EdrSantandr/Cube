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

protected:
	virtual void BeginPlay() override;
};
