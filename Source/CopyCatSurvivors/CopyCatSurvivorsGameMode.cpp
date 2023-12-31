// Copyright Epic Games, Inc. All Rights Reserved.

#include "CopyCatSurvivorsGameMode.h"
#include "CopyCatSurvivorsPlayerController.h"
#include "CopyCatSurvivorsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACopyCatSurvivorsGameMode::ACopyCatSurvivorsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACopyCatSurvivorsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_CrazyCatCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}