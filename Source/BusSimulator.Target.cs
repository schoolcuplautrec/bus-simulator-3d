using UnrealBuildTool;
using System.Collections.Generic;

public class BusSimulatorTarget : TargetRules
{
	public BusSimulatorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.Add("BusSimulator");
	}
}
