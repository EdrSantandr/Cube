// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CubeAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API UCubeAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UCubeAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
