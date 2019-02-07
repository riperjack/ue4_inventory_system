// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ue4_inventory_systemTarget : TargetRules
{
	public ue4_inventory_systemTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("ue4_inventory_system");
        ExtraModuleNames.Add("UMG");
    }
}
