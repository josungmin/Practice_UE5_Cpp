#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/ABCharacterBase.h"
#include "ABCharacterPlayer.generated.h"


UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()

public:
	AABCharacterPlayer();

protected:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
	TObjectPtr<class UCameraComponent> Camera;

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	//	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> QuaterMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> AttackAction;

	void Attack();
	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);
	void QuaterMove(const FInputActionValue& Value);
	void ChangeControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);

	ECharacterControlType CurrentCharacterControlType;

	virtual void SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
