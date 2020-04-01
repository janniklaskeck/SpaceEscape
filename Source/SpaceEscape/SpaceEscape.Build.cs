// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceEscape : ModuleRules
{
	public SpaceEscape(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Networking" });

        PrivateIncludePaths.AddRange(new string[]
        {
            "SpaceEscape/Prison",
            "SpaceEscape/Prison/Rooms",
            "SpaceEscape/Prison/Rooms/Puzzles",
            "SpaceEscape/Player",
            "SpaceEscape/GameMode",
            "SpaceEscape/Util"
        });
    }
}
