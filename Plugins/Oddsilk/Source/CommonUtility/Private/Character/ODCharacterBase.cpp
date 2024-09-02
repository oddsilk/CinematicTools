// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ODCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/ODCharacterControlData.h"
#include "Animation/AnimMontage.h"
#include "Character/ODComboActionData.h"
// Sets default values
AODCharacterBase::AODCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����ŷ ĳ���Ϳ� �����ϰ� �����Ϸ��� ĳ���Ͱ� ������ �ִ� �⺻ ������Ʈ�� ���� �پ��� �������� ������ ����� �Ǵµ���.
	//ĳ���� Ŭ������ ���캸�� �����ؼ� �ۼ��ϵ��� �ϰڽ��ϴ�. f12�� ���� charcterŬ������ �ҽ��ڵ带 Ž���غ� �� �ִ�.
		// private���� ����� �κ��� �����ܺ� �ʿ䰡 �ִ�. �ռ��� Actor�� �޽��� ���̱����� �츮�� ������ ��İ� �����ϰ� �����Ǿ� �ִ�.
		// ������ private�̱� ������ ���������� ������ �� �� ������ ���ԵǾ��ִ�. �׷��� GetMesh()�Լ�, getter�� ����ؼ� ��ӹ��� Ŭ������ �� �Լ��� ���ؼ� ������ �� �ִ�
		//�޽� ������Ʈ�� ���õ� �پ��� ������ �ڵ忡�� �̸� ������ ���ָ� �˴ϴ�. 


	//pawn�� �⺻����, // pawn�� ȸ���������ϱ� ���ؼ� �⺻������ �����ϴ� ���� // ī�޶� �ٷ궧 �ڼ��ϰ� �����ϵ��� �ϰڽ��ϴ�. 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); // ĸ���� ũ�⸦ �������ݴϴ�.
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn")); // ĸ���� �浹 ���������� �������ݴϴ�.

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // ĳ������ �̵������� ȸ���������� �������ݴϴ�.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ĳ������ ȸ���ӵ��� �������ݴϴ�.
	GetCharacterMovement()->JumpZVelocity = 400.0f; // ĳ������ �����ӵ��� �������ݴϴ�.
	GetCharacterMovement()->AirControl = 0.35f; // ĳ������ ���߿����� �̵��ӵ��� �������ݴϴ�.
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; // ĳ������ �ȱ�ӵ��� �������ݴϴ�.
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.1f; // ĳ������ �ּ� �ȱ�ӵ��� �������ݴϴ�.
	GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f; // ĳ������ �ȱ��� ���Ӽӵ��� �������ݴϴ�.

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-100.0f), FRotator(0.0f, -90.0f, 0.0f)); // �޽��� ��ġ�� ȸ���� �������ݴϴ�.
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint); // �޽��� �ִϸ��̼� ��带 �������ݴϴ�.
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh")); // �޽��� �浹 ���������� �������ݴϴ�.

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Oddsilk/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Oddsilk/Animation/ABP_ODCharacter.ABP_ODCharacter_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	// ������ ���� �ڷᱸ���� �����ڿ��� �ϼ������ݴϴ�
	static ConstructorHelpers::FObjectFinder<UODCharacterControlData> ShoulderDataRef(TEXT("/Script/CommonUtility.ODCharacterControlData'/Oddsilk/Data/CharacterControl/DA_Shoulder.DA_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Shoulder, ShoulderDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UODCharacterControlData> QuaterDataRef(TEXT("/Script/CommonUtility.ODCharacterControlData'/Oddsilk/Data/CharacterControl/DA_Quater.DA_Quater'"));
	if (QuaterDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Quater, QuaterDataRef.Object);
	}

// �ڲ� cpp���� ���۷����� �����ϴ� ���� �ٶ������� �ʽ��ϴ�. ������ �������ʹ� Blueprint�� Ȯ���ؼ� �����ϵ��� �ϰڽ��ϴ�. 

}



void AODCharacterBase::SetCharacterControlData(const UODCharacterControlData* CharacterControlData)
{
	//Pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	//CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;

}

void AODCharacterBase::ProcessComboCommand()
{
	if (CurrentCombo == 0)
	{
		ComboActionBegin();
		return;
	}


	if (!ComboTimerHandle.IsValid())
	{
		//Ÿ�̸� ������ ������ �Է��� ���Դٴ� ����, �̹� Ÿ�̸Ӱ� �ߵ��� �Ǿ �ñ⸦ ���ưų�, �޺��� ������ ���̻������� �ʿ䰡 ������ �ǹ��մϴ�.
		HasNextComboCommand = false;
	}
	else
	{
		//Ÿ�̸Ӱ� ��ȿ�ϴٸ�, üũ�ϱ� ������ ������������ �̵��� Ŀ�ǵ尡 �ߵ��ߴٴ� ���̱� ������ true�� �������ָ� �˴ϴ�. 
		HasNextComboCommand = true;
	}
}
void AODCharacterBase::ComboActionBegin()
{
	//Combo Status
	CurrentCombo = 1;

	//MovementSetting
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None); // None���� �����ϸ� �̵������ �������ϴ�. 
	
	//Animation Setting
	const float AttackSpeedRate = 1.0f;
	//��Ÿ�ָ� ����ϱ����ؼ��� AnimInsatnce�� �����͸� ���;��մϴ�. 
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage); // ��Ÿ�ָ� ����ϴ� Motage_Play�Լ��� ȣ���ϰ� �⺻�ӵ��� 1.0f�� ����ϵ��� �����մϴ�. 

	FOnMontageEnded EndDelegate; // ����üó�� �����ϰ� ���� �Լ��� Bind �Ѵ�
	EndDelegate.BindUObject(this, &AODCharacterBase::ComboActionEnd); // ��Ÿ�ְ� ������ ȣ���� �Լ��� �������ݴϴ�.
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer(); // �޺�Ÿ�̸Ӹ� �������ݴϴ�.
}

void AODCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsPropertyEnded)
{
	ensure(CurrentCombo != 0); // ���� �޺��� 0�� ����� ���ͼ��� �ȵǱ⶧���� üũ�մϴ�. // �μ��� �Լ���, ��� �α׿� ������ �߻��մϴ�.
	CurrentCombo = 0; // �޺��� �ʱ�ȭ�մϴ�.
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking); // ĳ������ �̵���带 �ٽ� �ȱ�� �������ݴϴ�.

}

void AODCharacterBase::SetComboCheckTimer()
{
	// �޺� �ε����� �������ݴϴ�. (����������,�ε����� ��ȿ������ �˻��ϱ����� DA�� �����Ѵ�)
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	const float AttackSpeedRate = 1.0f;
	float ComboEffetiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;

	if (ComboEffetiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AODCharacterBase::ComboCheck, ComboEffetiveTime, false);
	}
}

void AODCharacterBase::ComboCheck()
{
	ComboTimerHandle.Invalidate(); // Ÿ�̸Ӱ� �ٽ� ȣ����� �ʵ��� �������ݴϴ�. 

	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		//���� �޺����� �츮�������� �޺����� ����� �ȵǱ� ������  Clamp�� �ɾ��ݴϴ�.
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);

		//���� ���ǿ� ���� �̸� ������ �����ɴϴ�. �̶��� ��Ʈ���� ����ؾ��ϱ� ������ Printf�Լ��� ����մϴ�. 
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage); // �ش� ��Ÿ�� �������� �ٷ� Jump�մϴ�.
		SetComboCheckTimer(); // �޺�Ÿ�̸Ӹ� �ٽ� �������ݴϴ�.

		HasNextComboCommand = false; // �Է°��� �ʱ�ȭ
	}
}


