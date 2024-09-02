// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ODAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UODAnimInstance::UODAnimInstance()
{
	MovingThreshould = 3.0f;
	JumpingThreshould = 100.0f;
}

void UODAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// GetOwningActor �Լ��� ActorŸ������ ��ȯ �ϱ� ������ ĳ����Ŭ������ ����ȯ ������Ѵ�. 
	Owner = Cast <ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UODAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D(); // x,y���� ���ؼ� ������ �ӷ��� ���ϸ� �ȴ�. 
		bIsIdle = GroundSpeed < MovingThreshould; // ������ �ӵ��� �̵��ӵ����� ������ Idle���·� �Ǵ��Ѵ�.
		bIsFalling = Movement->IsFalling(); // �������� �ִ� ��(���鿡�� ������ �ִ���) üũ�ϸ� �ȴ�. 
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould); // �������� �ְ�, Z�ӵ��� �����ӵ����� ������ �������̶�� �Ǵ��Ѵ�.
	}
	//�����Ӹ��� ����ؼ� ������Ʈ�� �� ���̴�. 
	// ABP���� ��ӹ��� ������ �� ���ֵ��� �����ϰ�   
}
