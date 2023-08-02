#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Character/ABCharacterControlDataAsset.h"

AABCharacterBase::AABCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// SkeletalMesh Component
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CaracterMesh")); // ���� ���� ���� ĸ���������� �ƴ� ����� �浹ó���� �ʿ��� ��� �޽����� �浹ó���� �Ѵ�.

	// CharacterMovement Component
	GetCharacterMovement()->bOrientRotationToMovement = true; // �̵� �� �ش� �������� ȸ���� ��ų ������ ����
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f; // ���߿��� �̵� �� ����
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f; // �̵� �� ���� �� ���� ��

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/ArenaBattle/Animation/ABP_Player.ABP_Player_C"));
	if (CharacterAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	}

	// Control Data Section
	static ConstructorHelpers::FObjectFinder<UABCharacterControlDataAsset> ShoulderDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlDataAsset'/Game/ArenaBattle/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManaer.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UABCharacterControlDataAsset> QuaterDataRef(TEXT("/Script/ArenaBattle.ABCharacterControlDataAsset'/Game/ArenaBattle/CharacterControl/ABC_Quater.ABC_Quater'"));
	if (QuaterDataRef.Object)
	{
		CharacterControlManaer.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}
}

void AABCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AABCharacterBase::SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData)
{
	bUseControllerRotationYaw = CharacterControlData->bUseControlRotationYaw;
	bUseControllerRotationPitch = CharacterControlData->bUseControlRotationPitch;
	bUseControllerRotationRoll = CharacterControlData->bUseControlRotationRoll;

	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
}

