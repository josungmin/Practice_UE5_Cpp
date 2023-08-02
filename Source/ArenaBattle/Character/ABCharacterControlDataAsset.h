#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABCharacterControlDataAsset.generated.h"

UCLASS()
class ARENABATTLE_API UABCharacterControlDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UABCharacterControlDataAsset();

	// Pawn Section
	UPROPERTY(EditAnyWhere, Category = Pawn)
	uint32 bUseControlRotationYaw : 1;   // bool type 사용시 메모리 크기가 불확정 따라서 비트 사인 사용

	UPROPERTY(EditAnyWhere, Category = Pawn)
	uint32 bUseControlRotationPitch : 1;

	UPROPERTY(EditAnyWhere, Category = Pawn)
	uint32 bUseControlRotationRoll : 1;


	// Character Movement Section
	UPROPERTY(EditAnyWhere, Category = CharacterMovement)
	FRotator RotationRate;

	UPROPERTY(EditAnyWhere, Category = CharacterMovement)
	uint32 bUseControllerDesiredRotation : 1; // 방향 전환 시 회전 유무

	UPROPERTY(EditAnyWhere, Category = CharacterMovement)
	uint32 bOrientRotationToMovement : 1; // 이동 방향으로 회전 


	// Input Movement Section
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;


	// Spring Arm Section
	UPROPERTY(EditAnyWhere, Category = SpringArm)
	float TargetArmLength;

	UPROPERTY(EditAnyWhere, Category = SpringArm)
	FRotator RelativeRotation;

	UPROPERTY(EditAnyWhere, Category = SpringArm)
	uint32 bUsePawnControlRotation : 1;

	UPROPERTY(EditAnyWhere, Category = SpringArm)
	uint32 bDoCollisionTest : 1;

	UPROPERTY(EditAnyWhere, Category = SpringArm)
	uint32 bInheritYaw : 1;

	UPROPERTY(EditAnyWhere, Category = SpringArm)
	uint32 bInheritRoll : 1;

	UPROPERTY(EditAnyWhere, Category = SpringArm)
	uint32 bInheritPitch : 1;
};
