// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class DriftSyndicateTarget : TargetRules
{
	public DriftSyndicateTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		bUseLoggingInShipping = true;
        bOverrideBuildEnvironment = true;
		GlobalDefinitions.Add("UE_BUILD_SHIPPING_WITH_LOGGING=1");

		ExtraModuleNames.AddRange( new string[] { "DriftSyndicate" } );
	}
}
