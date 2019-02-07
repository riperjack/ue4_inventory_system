// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ue4_inventory_systemGameMode.h"
#include "ue4_inventory_systemHUD.h"
#include "ue4_inventory_systemCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aue4_inventory_systemGameMode::Aue4_inventory_systemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Aue4_inventory_systemHUD::StaticClass();
}
