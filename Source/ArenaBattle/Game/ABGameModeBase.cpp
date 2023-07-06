#include "Game/ABGameModeBase.h"

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
		TEXT("/Script/CoreUObject.Class'/Script/ArenaBattle.ABCharacterPlayer'"));
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

