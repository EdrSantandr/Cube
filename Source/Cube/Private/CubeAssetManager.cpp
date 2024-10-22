// Copyright EderSantander developer


#include "CubeAssetManager.h"
#include "CubeGameplayTags.h"

UCubeAssetManager& UCubeAssetManager::Get()
{
	check(GEngine);
	UCubeAssetManager* CubeAssetManager = Cast<UCubeAssetManager>(GEngine->AssetManager);
	return *CubeAssetManager;
}

void UCubeAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FCubeGameplayTags::InitializeGameplayTags();
}
