using UnrealBuildTool;

public class DriftSyndicate : ModuleRules
{
    public DriftSyndicate(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "GameplayTags"
    });
    }
}