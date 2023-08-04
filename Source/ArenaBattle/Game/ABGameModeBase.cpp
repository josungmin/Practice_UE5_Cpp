#include "Game/ABGameModeBase.h"
#include "Character/ABCharacterNonPlayer.h"
#include "Math/UnrealMathUtility.h"

AABGameModeBase::AABGameModeBase()
{
	// Default Pawn Class
	//static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(
	//	TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	//if (ThirdPersonClassRef.Class)
	//{
	//	DefaultPawnClass = ThirdPersonClassRef.Class;
	//}

	static ConstructorHelpers::FClassFinder<APawn> TDefaultPawnClassRef(
		TEXT("/Game/ArenaBattle/Character/BP_CharacterPlayer.BP_CharacterPlayer_C"));
	if (TDefaultPawnClassRef.Class)
	{
		DefaultPawnClass = TDefaultPawnClassRef.Class;
	}

	// Player Controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(
		TEXT("/Script/ArenaBattle.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	///Script/CoreUObject.Class'/Script/ArenaBattle.ABCharacterPlayer'
}

void AABGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnCharacter();
	

}

void AABGameModeBase::SpawnCharacter()
{
	FActorSpawnParameters params;
	FVector Location = FVector(FMath::RandRange(-800.0f, 800.0f), FMath::RandRange(-800.0f, 800.0f), 90);
	FRotator Rotation = FRotator(0, 180, 0);

	GetWorld()->SpawnActor<ACharacter>(AABCharacterNonPlayer::StaticClass(), Location, Rotation, params);

}


