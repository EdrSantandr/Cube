// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CubeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CUBE_API ACubeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Music")
	TArray<AActor*> GetActorsDebussy() { return ActorsDebussy; }

	UFUNCTION(BlueprintCallable, Category="Music")
	TArray<AActor*> GetActorsNyeh() { return ActorsNyeh; }

	UFUNCTION(BlueprintCallable, Category="Music")
	void CallDebussyShoot();

	UFUNCTION(BlueprintCallable, Category="Music")
	void CallNyehShoot();

private:

	UPROPERTY()
	TArray<AActor*> ActorsDebussy;

	UPROPERTY()
	TArray<AActor*> ActorsNyeh;
};

