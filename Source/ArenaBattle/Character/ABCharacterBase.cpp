#include "Character/ABCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "Character/ABCharacterControlDataAsset.h"
#include "Character/ABComboActionData.h"
#include "Character/ABCharacterNonPlayer.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ABGameModeBase.h"

AABCharacterBase::AABCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCapsule"));

	// SkeletalMesh Component
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision")); // 대전 게임 같이 캡슐영역만이 아닌 면밀한 충돌처리가 필요한 경우 메쉬에도 충돌처리를 한다.

	// CharacterMovement Component
	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 시 해당 방향으로 회전을 시킬 것인지 지정
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f; // 공중에서 이동 시 감속
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f; // 이동 중 정지 시 제동 값

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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("Script/Engine.AnimMontage'/Game/ArenaBattle/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
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


void AABCharacterBase::ProcessComboAttack()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegine();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboCommand = false;
	}
	else
	{
		HasNextComboCommand = true;
	}
}


void AABCharacterBase::ComboActionBegine()
{
	const float attackSpeedRate = 1.0f;
	
	CurrentCombo = 1;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_Play(ComboActionMontage, attackSpeedRate);

	FOnMontageEnded endDelegate;
	endDelegate.BindUObject(this, &AABCharacterBase::ComboActionEnd);
	animInstance->Montage_SetEndDelegate(endDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimmer();
}


void AABCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsEnded)
{
	CurrentCombo = 0;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


void AABCharacterBase::SetComboCheckTimmer()
{
	int32 comboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(comboIndex));

	const float attackSpeedRate = 1.0f;

	float ComboEffeciveTime = (ComboActionData->EffectiveFrameCount[comboIndex] / ComboActionData->FrameRate) / attackSpeedRate;

	if (ComboEffeciveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AABCharacterBase::ComboCheck, ComboEffeciveTime, false);
	}
}

void AABCharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate();

	if (HasNextComboCommand)
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);

		FName NextSectionName = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionPrefix, CurrentCombo);

		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		animInstance->Montage_JumpToSection(NextSectionName, ComboActionMontage);

		SetComboCheckTimmer();
		HasNextComboCommand = false;
	}
}


void AABCharacterBase::SetDead()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->StopAllMontages(0.0f);
	animInstance->Montage_Play(DeadMontage);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AABGameModeBase* GameMode = Cast<AABGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	FTimerHandle WaitHandle;
	float WaitTime = 3.0f; 
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{		
			GameMode->SpawnCharacter();
		}), WaitTime, false);
}

float AABCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetDead();

	return Damage;
}


void AABCharacterBase::AttackHitCheck()
{
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	FHitResult outHitResult;
	const float attackRange = 150.0f;
	const float radius = 50.0f;

	const FVector start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector end = start + GetActorForwardVector() * attackRange;

	bool bIsHit = GetWorld()->SweepSingleByChannel(outHitResult, start, end, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(radius), Params);

	if (bIsHit)
	{
		FDamageEvent DamageEvent;
		outHitResult.GetActor()->TakeDamage(100.0f, DamageEvent, GetController(), this);
	}

#if ENABLE_DRAW_DEBUG
	FVector capsulePosition = start + (end - start) / 2.0f;
	float halfHeight = attackRange / 2.0f;
	FColor color = bIsHit ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), capsulePosition, halfHeight, radius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), color, false, 3.0f);

#endif
}
