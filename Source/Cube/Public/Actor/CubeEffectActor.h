// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeEffectActor.generated.h"

class UGameplayEffect;
class UBoxComponent;

UENUM()
enum class EAppliedAbilityEffectType : uint8
{
	Instant,
	Duration,
	Infinite
};

UCLASS()
class CUBE_API ACubeEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	ACubeEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	EAppliedAbilityEffectType EffectType = EAppliedAbilityEffectType::Instant;
	
	UPROPERTY(EditAnywhere, Category="InstantEffect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;

	UPROPERTY(EditAnywhere, Category="DurationEffect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffect;

	UPROPERTY(EditAnywhere, Category="InfiniteEffect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffect;
	
	UFUNCTION(BlueprintCallable, Category="Effects")
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
