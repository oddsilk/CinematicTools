// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ODPlayerController.h"

void AODPlayerController::BeginPlay()
{
	Super::BeginPlay(); // ��ӹ��� �Լ��� ������ super�� ȣ������� �մϴ�.

	FInputModeGameOnly GameOnlyInputMode; // FInputModeGameOnly ����ü ����
	SetInputMode(GameOnlyInputMode); // �������ڸ��� ���콺 ��Ŀ���� ����Ʈ ������ ���� �˴ϴ�. 
}
