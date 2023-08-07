#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API AABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AABGameModeBase();
	
private:
	UPROPERTY(EditAnyWhere)
		TSubclassOf<ACharacter> Enemy;

	TArray<class AABCharacterNonPlayer*> Enemies;

protected:
	virtual void BeginPlay() override;

public:
	void SpawnCharacter();
};

