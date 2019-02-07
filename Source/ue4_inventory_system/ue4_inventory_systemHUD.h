// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ue4_inventory_systemHUD.generated.h"

UCLASS()
class Aue4_inventory_systemHUD : public AHUD
{
	GENERATED_BODY()

public:
	Aue4_inventory_systemHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};

