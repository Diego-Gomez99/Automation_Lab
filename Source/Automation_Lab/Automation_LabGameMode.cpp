// Copyright Epic Games, Inc. All Rights Reserved.

#include "Automation_LabGameMode.h"
#include "Automation_LabCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAutomation_LabGameMode::AAutomation_LabGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
