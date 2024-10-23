// Copyright EderSantander developer

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInformation.generated.h"

USTRUCT(BlueprintType)
struct FUAttributeInformation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

UCLASS()
class CUBE_API UAttributeInformation : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION()
	FUAttributeInformation FindAttributeInfoByTag(const FGameplayTag& InAttributeTag, bool bLogNotFound = false);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FUAttributeInformation> AttributeInformation;
};
