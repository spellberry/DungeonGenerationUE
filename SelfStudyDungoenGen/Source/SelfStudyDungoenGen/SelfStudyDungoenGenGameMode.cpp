// Copyright Epic Games, Inc. All Rights Reserved.

#include "SelfStudyDungoenGenGameMode.h"
#include "SelfStudyDungoenGenCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASelfStudyDungoenGenGameMode::ASelfStudyDungoenGenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
