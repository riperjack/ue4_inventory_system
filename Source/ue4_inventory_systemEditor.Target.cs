// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ue4_inventory_systemEditorTarget : TargetRules
{
	public ue4_inventory_systemEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("ue4_inventory_system");
        ExtraModuleNames.Add("UMG");
    }
}
