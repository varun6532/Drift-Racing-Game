using UnrealBuildTool;
using System.Collections.Generic;

public class DriftSyndicateEditorTarget : TargetRules
{
    public DriftSyndicateEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        bUseLoggingInShipping = true;
        bOverrideBuildEnvironment = true;
		

        ExtraModuleNames.AddRange(new string[] { "DriftSyndicate" });
    }
}