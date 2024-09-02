// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ODCharacterBase.h"
#include "InputActionValue.h"// FInputActionValue�� ����ϱ� ���ؼ� �߰��մϴ�. // EnhancedInput����� build.cs�� �߰��Ǿ� �־�� �մϴ�.

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
	// Meta = (AllowPrivateAccess = "true") �� private ������  �������Ʈ������ ������ �� �ֵ��� ���ִ� �������Դϴ�. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

//input section
protected:
	// ������ �ٸ������� ������ �� �ֵ��� �ϱ� ���ؼ� EditAnywhere�� �����մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr <class UInputMappingContext> DefaultMappingContext; 
	// 3��Ī ���ø����� �����ϰ� �ִ� ���� �״�� ����ϰڽ��ϴ�.




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
