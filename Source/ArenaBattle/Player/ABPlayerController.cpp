#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 게임 화면에 마우스 포커싱
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
