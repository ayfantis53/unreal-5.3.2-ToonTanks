// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
//             																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

using UnrealBuildTool;
using System.Collections.Generic;

public class ToonTanksEditorTarget : TargetRules
{
	public ToonTanksEditorTarget(TargetInfo Target) : base(Target)
	{
		Type                 = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] 
		{ 
			"ToonTanks",
		  	"Tests", 
		} );
	}
}
