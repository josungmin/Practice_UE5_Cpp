#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "ABCharacterPlayer.generated.h"


UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()

public:
	AABCharacterPlayer();
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
	TObjectPtr<class UCameraComponent> Camera;
};
