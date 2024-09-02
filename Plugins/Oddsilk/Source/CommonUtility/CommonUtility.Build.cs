// Copyright Oddsilk, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CommonUtility : ModuleRules
{
    public CommonUtility(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //경로 검증: PublicIncludePaths에 명시된 경로가 실제로 유효한지 확인하세요. 이 경로가 존재하지 않는다면, 적절한 실제 경로로 수정하거나 제거해야 합니다.
       //PublicIncludePaths.AddRange(new string[] { "CommonUtility" });

        //plugins 폴더의 puglicIncludPaths.AddRange를 하자
        PrivateIncludePaths.AddRange(new string[] {  }); // "Character", "Game",  "Player",  "Prop"

        //의존성 확인: EnhancedInput 모듈이 PublicDependencyModuleNames에 포함되어 있음을 확인했습니다. 
        //이는 모듈이 이 의존성을 요구하고 있으며, 이전에 .uplugin 파일에서의 의존성 추가가 올바른 조치였음을 확인시켜 줍니다.
        PublicDependencyModuleNames.AddRange(new string[] {"Core","CoreUObject","Engine", "InputCore", "EnhancedInput", });
        
        PrivateDependencyModuleNames.AddRange(new string[] {});

        //Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[]{"Slate","SlateCore"});

        //Uncomment if youre using online features
        //PrivateDependencyModuleNames.Add("OnlineSubsystem");

        //To include OnlineSubSystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}



