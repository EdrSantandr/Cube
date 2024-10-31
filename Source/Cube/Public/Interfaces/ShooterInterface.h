// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShooterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UShooterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CUBE_API IShooterInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PerformShoot();
};
