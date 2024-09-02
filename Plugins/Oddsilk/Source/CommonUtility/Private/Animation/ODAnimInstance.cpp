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
	// GetOwningActor 함수는 Actor타입으로 반환 하기 때문에 캐릭터클래스로 형변환 해줘야한다. 
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
		GroundSpeed = Velocity.Size2D(); // x,y값만 구해서 지면의 속력을 구하면 된다. 
		bIsIdle = GroundSpeed < MovingThreshould; // 지면의 속도가 이동속도보다 작으면 Idle상태로 판단한다.
		bIsFalling = Movement->IsFalling(); // 떨어지고 있는 지(지면에서 떨어져 있는지) 체크하면 된다. 
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould); // 떨어지고 있고, Z속도가 점프속도보다 높으면 점프중이라고 판단한다.
	}
	//프레임마다 계속해서 업데이트가 될 것이다. 
	// ABP에서 상속받은 변수를 볼 수있도록 설정하고   
}
