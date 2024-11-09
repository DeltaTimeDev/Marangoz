// Copyright Epic Games, Inc. All Rights Reserved.

#include "Framework/MarangozGameMode.h"
#include "Framework/MarangozCharacter.h"
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
