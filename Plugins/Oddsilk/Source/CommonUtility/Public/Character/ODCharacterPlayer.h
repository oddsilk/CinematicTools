// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ODCharacterBase.h"
#include "InputActionValue.h"// FInputActionValue을 사용하기 위해서 추가합니다. // EnhancedInput모듈이 build.cs에 추가되어 있어야 합니다.

#include "ODCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUTILITY_API AODCharacterPlayer : public AODCharacterBase
{
	GENERATED_BODY()
public:
	AODCharacterPlayer();
protected:
	virtual void BeginPlay() override;
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


//CharacterControl Section
protected:
	void ChangeCharacterControl();
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class UODCharacterControlData* CharacterControlData) override;


//camera section
protected:
	// Meta = (AllowPrivateAccess = "true") 는 private 변수에  블루프린트에서도 접근할 수 있도록 해주는 지시자입니다. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

//input section
protected:
	// 에셋은 다른곳에서 변경할 수 있도록 하기 위해서 EditAnywhere로 설정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr <class UInputMappingContext> DefaultMappingContext; 
	// 3인칭 템플릿에서 제공하고 있는 것을 그대로 사용하겠습니다.




	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr< class UInputAction> ShoulderMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr< class UInputAction> QuaterMoveAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr< class UInputAction> AttackAction;
	
	

	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);
	void QuaterMove(const FInputActionValue& Value);

	ECharacterControlType CurrentCharacterControlType;

	void Attack();

};
