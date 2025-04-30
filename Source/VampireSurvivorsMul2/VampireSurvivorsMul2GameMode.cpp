// Copyright Epic Games, Inc. All Rights Reserved.

#include "VampireSurvivorsMul2GameMode.h"
#include "VampireSurvivorsMul2Character.h"
#include "UObject/ConstructorHelpers.h"

AVampireSurvivorsMul2GameMode::AVampireSurvivorsMul2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
