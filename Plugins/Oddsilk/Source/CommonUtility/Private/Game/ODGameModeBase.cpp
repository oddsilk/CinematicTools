// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ODGameModeBase.h"
// #include "Player/ODPlayerController.h" // �������� ������ ��� �̷��� ��������� include�� �ʿ䰡 ����.


AODGameModeBase::AODGameModeBase()
{

	//DefaultPawnClass 
	// cppŬ������ �ƴ϶� Content ������ asset���� Ŭ���� ������ ���;� �մϴ�. // ��Ŭ��- copy reference�� ��θ� ���� �� �ֽ��ϴ�.
	// ������ �ڵ��̱⶧���� ConstructorHelpers::FClassFinder�� ����Ͽ� ���� ������ ������ �� �ֽ��ϴ�.
	// �߿��� �� , ũ������ ������ ������ ���̱� ������ ( /Script/Engine.Blueprint'  )�� (  '  )�� �������ְ� , �������Ʈ Ŭ������ ������ ������ ���̱� ������ (  _C )�� �߰��Ѵ�

	
	static ConstructorHelpers::FClassFinder<APawn>ThirdPersonClassRef(TEXT("/Oddsilk/Blueprint/BP_ODCharacterPlayer.BP_ODCharacterPlayer_C"));
	if (ThirdPersonClassRef.Class)
	{
		// null check  Ŭ������ ���� ������ null�� �ƴϸ�	 Pawnclass ����
		DefaultPawnClass = ThirdPersonClassRef.Class;
	}



	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CommonUtility.ODPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
	// ���� ���� cppŬ������ ������ include �� static class�� ���� �� ������ header������ include�ϴ� �� ���� ��ó�� �������� reference�� �������� ���� ����.
	//PlayerControllerClass = AODPlayerController::StaticClass(); // ������ ������ʿ䰡 ����.
}
 