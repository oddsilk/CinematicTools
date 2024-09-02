// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ODCharacterControlData.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUTILITY_API UODCharacterControlData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public: 
	UODCharacterControlData();

	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControllerRotationYaw : 1;  // Pawn ���ǿ��� ControlRotation�� Yaw���� �ַ� üũ�� �մϴ�. 
	// �ش� ���� üũ�� ���� ���� ������ �ϱ� ���� ���� 

	// CharacterMovement ����
	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bOrientRotationToMovement : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bUseControllerDesiredRotation : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	FRotator RotationRate;


	// ������ ����� �Է� ���� ���ؽ�Ʈ�� ���� �������
	UPROPERTY(EditAnywhere,BlueprintReadOnly,  Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;


	//SprintArm ����
	UPROPERTY(EditAnywhere, Category = SprintArm)
	float TargetArmLength;

	UPROPERTY(EditAnywhere, Category = SprintArm)
	FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, Category = SprintArm)
	uint32 bUsePawnControlRotation : 1;

	UPROPERTY(EditAnywhere, Category = SprintArm)
	uint32 bInheritPitch : 1;

	UPROPERTY(EditAnywhere, Category = SprintArm)
	uint32 bInheritYaw : 1;

	UPROPERTY(EditAnywhere, Category = SprintArm)
	uint32 bInheritRoll : 1;
	
	UPROPERTY(EditAnywhere, Category = SprintArm)
	uint32 bDoCollisionTest : 1;

};
