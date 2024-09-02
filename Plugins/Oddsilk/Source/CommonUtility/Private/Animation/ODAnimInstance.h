// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ODAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUTILITY_API UODAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UODAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override; //initialize
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // tick


	// Anim Instance�� �����ϰ��ִ� ĳ������ ������ ��´�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character )
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	//bool Ÿ���� ����� ��� ���� ��Ȯ���� �ʱ⶧����	,  intager������ �����ϵ� b���λ縦 ���̰�, ��Ʈ �÷��� : �� �������ش�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character) 
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;
};
