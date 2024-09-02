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


	// Anim Instance를 소유하고있는 캐릭터의 정보를 담는다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character )
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	//bool 타입은 사이즈가 어떻게 될지 명확하지 않기때문에	,  intager형으로 선언하되 b접두사를 붙이고, 비트 플래그 : 를 지정해준다.
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
