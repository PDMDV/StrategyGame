// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GrandStrategyGame : ModuleRules
{
	public GrandStrategyGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "PCG", "Core", "CoreUObject", "Engine", "InputCore", "Voronoi", "GeometryCore", "GeometryFramework", "GeometryScriptingCore", "GeometryScriptingEditor", "GeometryAlgorithms", "DynamicMesh", "GameplayTags", "GameplayAbilities", "GameplayTasks", "AIModule", "Slate", "SlateCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "PCG", "Voronoi", "GeometryCore", "GeometryFramework", "GeometryScriptingCore", "GeometryScriptingEditor", "GeometryAlgorithms", "DynamicMesh", "ModelingComponents", "ModelingComponents", "ModelingComponents", "AIModule", "AIModule", "AIModule", "GameplayTasks", "Slate", "SlateCore", "UMG", "MutableRuntime" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
