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

UENUM(BlueprintType)
enum class EEffectCustomRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UENUM(BlueprintType)
enum class EEffectCustomApplicationPolicy : uint8
{
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
	DoNotApply
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

	UFUNCTION(BlueprintCallable)
	void OnActorBeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnActorEndOverlap(AActor* TargetActor);

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	bool bRemoveOnEffectRemoval = false;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	EAppliedAbilityEffectType EffectType = EAppliedAbilityEffectType::Instant;
	
	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;

	UPROPERTY(EditAnywhere, Category="Effects")
	EEffectCustomApplicationPolicy InstantApplicationPolicy = EEffectCustomApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffect;

	UPROPERTY(EditAnywhere, Category="Effects")
	EEffectCustomApplicationPolicy DurationApplicationPolicy = EEffectCustomApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffect;

	UPROPERTY(EditAnywhere, Category="Effects")
	EEffectCustomApplicationPolicy InfiniteApplicationPolicy = EEffectCustomApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, Category="Effects")
	EEffectCustomRemovalPolicy InfiniteRemovalPolicy = EEffectCustomRemovalPolicy::RemoveOnEndOverlap;
	
	UFUNCTION(BlueprintCallable, Category="Effects")
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
