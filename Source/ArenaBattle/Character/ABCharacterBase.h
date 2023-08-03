#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AABCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnyWhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
		TMap<ECharacterControlType, class UABCharacterControlDataAsset*> CharacterControlManaer;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Animation)
		TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AttackData, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UABComboActionData> ComboActionData;

protected:
	virtual void SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData);
	
	void ProcessComboAttack();
	void ComboActionBegine();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsEnded);

	void SetComboCheckTimmer();
	void ComboCheck();

protected:
	int32 CurrentCombo = 0;
	
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false;
};
