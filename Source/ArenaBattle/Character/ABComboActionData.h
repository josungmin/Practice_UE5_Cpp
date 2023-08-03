#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABComboActionData.generated.h"


UCLASS()
class ARENABATTLE_API UABComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UABComboActionData();

public:
	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionPrefix;

	UPROPERTY(EditAnywhere, Category = Name)
		uint8 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = Name)
		float FrameRate;

	UPROPERTY(EditAnywhere, Category = ComboData)
		TArray<float> EffectiveFrameCount;
};
