// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ODPlayerController.h"

void AODPlayerController::BeginPlay()
{
	Super::BeginPlay(); // 상속받은 함수는 무조건 super를 호출해줘야 합니다.

	FInputModeGameOnly GameOnlyInputMode; // FInputModeGameOnly 구조체 선언
	SetInputMode(GameOnlyInputMode); // 시작하자마자 마우스 포커스가 뷰포트 안으로 들어가게 됩니다. 
}
