// Copyright Oddsilk, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CommonUtility : ModuleRules
{
    public CommonUtility(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        //��� ����: PublicIncludePaths�� ��õ� ��ΰ� ������ ��ȿ���� Ȯ���ϼ���. �� ��ΰ� �������� �ʴ´ٸ�, ������ ���� ��η� �����ϰų� �����ؾ� �մϴ�.
       //PublicIncludePaths.AddRange(new string[] { "CommonUtility" });

        //plugins ������ puglicIncludPaths.AddRange�� ����
        PrivateIncludePaths.AddRange(new string[] {  }); // "Character", "Game",  "Player",  "Prop"

        //������ Ȯ��: EnhancedInput ����� PublicDependencyModuleNames�� ���ԵǾ� ������ Ȯ���߽��ϴ�. 
        //�̴� ����� �� �������� �䱸�ϰ� ������, ������ .uplugin ���Ͽ����� ������ �߰��� �ùٸ� ��ġ������ Ȯ�ν��� �ݴϴ�.
        PublicDependencyModuleNames.AddRange(new string[] {"Core","CoreUObject","Engine", "InputCore", "EnhancedInput", });
        
        PrivateDependencyModuleNames.AddRange(new string[] {});

        //Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[]{"Slate","SlateCore"});

        //Uncomment if youre using online features
        //PrivateDependencyModuleNames.Add("OnlineSubsystem");

        //To include OnlineSubSystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}



