#include "Animation/ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	MoveThreshould = 3.0f;
	JumpThreshould = 100.0f;
}

void UABAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();

		bIsRunning = MoveThreshould < GroundSpeed;

		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpThreshould);
	}
}