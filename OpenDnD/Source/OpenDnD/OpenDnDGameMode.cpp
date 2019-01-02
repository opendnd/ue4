// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "OpenDnDGameMode.h"
#include "Persons/DPlayableCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOpenDnDGameMode::AOpenDnDGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Persons/BP_PlayableCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
