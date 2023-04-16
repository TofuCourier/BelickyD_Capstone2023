// Copyright Epic Games, Inc. All Rights Reserved.

#include "CapstoneGameMode.h"
#include "CapstoneCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACapstoneGameMode::ACapstoneGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;*/

}
