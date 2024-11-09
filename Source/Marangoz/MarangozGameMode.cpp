// Copyright Epic Games, Inc. All Rights Reserved.

#include "MarangozGameMode.h"
#include "MarangozCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMarangozGameMode::AMarangozGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
