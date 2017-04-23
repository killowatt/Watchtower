// Copyright 2017 William Yates

using UnrealBuildTool;
using System.Collections.Generic;

public class WatchtowerTarget : TargetRules
{
	public WatchtowerTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "Watchtower" } );
	}
}
