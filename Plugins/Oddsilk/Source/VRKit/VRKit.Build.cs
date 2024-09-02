// Copyright Oddsilk, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VRKit : ModuleRules
{
    public VRKit(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new string[] { });
        
        PublicDependencyModuleNames.AddRange(new string[] {"Core","CoreUObject","Engine", "InputCore", "EnhancedInput", });
        
        PrivateDependencyModuleNames.AddRange(new string[] {});

        //Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[]{"Slate","SlateCore"});

        //Uncomment if youre using online features
        //PrivateDependencyModuleNames.Add("OnlineSubsystem");

        //To include OnlineSubSystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}



