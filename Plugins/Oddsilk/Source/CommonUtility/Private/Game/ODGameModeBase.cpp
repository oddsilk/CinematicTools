// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ODGameModeBase.h"
// #include "Player/ODPlayerController.h" // 에셋으로 가져올 경우 이렇게 헤더파일을 include할 필요가 없다.


AODGameModeBase::AODGameModeBase()
{

	//DefaultPawnClass 
	// cpp클래스가 아니라서 Content 폴더의 asset에서 클래스 정보를 얻어와야 합니다. // 우클릭- copy reference로 경로를 얻어올 수 있습니다.
	// 생성자 코드이기때문에 ConstructorHelpers::FClassFinder를 사용하여 에셋 정보를 가져올 수 있습니다.
	// 중요한 건 , 크래스의 정보를 가져올 것이기 때문에 ( /Script/Engine.Blueprint'  )와 (  '  )는 제거해주고 , 블루프린트 클래스의 정보를 가져올 것이기 때문에 (  _C )를 추가한다

	
	static ConstructorHelpers::FClassFinder<APawn>ThirdPersonClassRef(TEXT("/Oddsilk/Blueprint/BP_ODCharacterPlayer.BP_ODCharacterPlayer_C"));
	if (ThirdPersonClassRef.Class)
	{
		// null check  클래스의 내부 정보가 null이 아니면	 Pawnclass 세팅
		DefaultPawnClass = ThirdPersonClassRef.Class;
	}



	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CommonUtility.ODPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
	// 직접 만든 cpp클래스기 때문에 include 후 static class로 세할 수 있지만 header파일을 include하는 것 보다 위처럼 에셋으로 reference를 가져오는 것이 좋다.
	//PlayerControllerClass = AODPlayerController::StaticClass(); // 이제는 사용할필요가 없다.
}
 