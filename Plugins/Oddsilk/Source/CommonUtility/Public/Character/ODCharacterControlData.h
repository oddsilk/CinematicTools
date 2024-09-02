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
	uint32 bUseControllerRotationYaw : 1;  // Pawn 섹션에서 ControlRotation의 Yaw값을 주로 체크를 합니다. 
	// 해당 값만 체크를 할지 말지 결정을 하기 위한 변수 

	// CharacterMovement 섹션
	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bOrientRotationToMovement : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bUseControllerDesiredRotation : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	FRotator RotationRate;


	// 앞으로 사용할 입력 맵핑 컨텍스트를 담을 멤버변수
	UPROPERTY(EditAnywhere,BlueprintReadOnly,  Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;


	//SprintArm 섹션
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
