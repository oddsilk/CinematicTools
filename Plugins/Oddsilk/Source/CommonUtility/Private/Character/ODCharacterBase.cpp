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

	// 마네킹 캐릭터와 동일하게 설정하려면 캐릭터가 가지고 있는 기본 컴포넌트에 대한 다양한 설정들이 진행을 해줘야 되는데요.
	//캐릭터 클래스를 살펴보고 참고해서 작성하도록 하겠습니다. f12를 통해 charcter클래스의 소스코드를 탐구해볼 수 있다.
		// private으로 선언된 부분을 눈여겨볼 필요가 있다. 앞서서 Actor에 메쉬를 붙이기위해 우리가 설계한 방식과 유사하게 지정되어 있다.
		// 하지만 private이기 때문에 직접적으로 접근을 할 수 없도록 설게되어있다. 그래서 GetMesh()함수, getter를 사용해서 상속받은 클래스가 이 함수를 통해서 접근할 수 있다
		//메쉬 컴포넌트와 관련된 다양한 생성자 코드에서 미리 지정만 해주면 됩니다. 


	//pawn의 기본설정, // pawn의 회전을지정하기 위해서 기본적으로 세팅하는 값들 // 카메라를 다룰때 자세하게 설명하도록 하겠습니다. 
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f); // 캡슐의 크기를 지정해줍니다.
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn")); // 캡슐의 충돌 프로파일을 지정해줍니다.

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터의 이동방향을 회전방향으로 지정해줍니다.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 캐릭터의 회전속도를 지정해줍니다.
	GetCharacterMovement()->JumpZVelocity = 400.0f; // 캐릭터의 점프속도를 지정해줍니다.
	GetCharacterMovement()->AirControl = 0.35f; // 캐릭터의 공중에서의 이동속도를 지정해줍니다.
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; // 캐릭터의 걷기속도를 지정해줍니다.
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.1f; // 캐릭터의 최소 걷기속도를 지정해줍니다.
	GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f; // 캐릭터의 걷기중 감속속도를 지정해줍니다.

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f,0.0f,-100.0f), FRotator(0.0f, -90.0f, 0.0f)); // 메쉬의 위치와 회전을 지정해줍니다.
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint); // 메쉬의 애니메이션 모드를 지정해줍니다.
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh")); // 메쉬의 충돌 프로파일을 지정해줍니다.

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

	// 데이터 맵의 자료구조를 생성자에서 완성시켜줍니다
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

// 자꾸 cpp에서 레퍼런스로 변경하는 것은 바람직하지 않습니다. 때문에 이제부터는 Blueprint로 확장해서 지정하도록 하겠습니다. 

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
		//타이머 설정이 없을때 입력이 들어왔다느 것은, 이미 타이머가 발동이 되어서 시기를 놓쳤거나, 콤보가 끝나서 더이상진행할 필요가 없음을 의미합니다.
		HasNextComboCommand = false;
	}
	else
	{
		//타이머가 유효하다면, 체크하기 이전에 다음섹션으로 이동할 커맨드가 발동했다는 뜻이기 때문에 true로 설정해주면 됩니다. 
		HasNextComboCommand = true;
	}
}
void AODCharacterBase::ComboActionBegin()
{
	//Combo Status
	CurrentCombo = 1;

	//MovementSetting
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None); // None으로 지정하면 이동기능이 없어집니다. 
	
	//Animation Setting
	const float AttackSpeedRate = 1.0f;
	//몽타주를 재생하기위해서는 AnimInsatnce의 포인터를 얻어와야합니다. 
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(ComboActionMontage); // 몽타주를 재생하는 Motage_Play함수를 호출하고 기본속도인 1.0f로 재생하도록 설정합니다. 

	FOnMontageEnded EndDelegate; // 구조체처럼 선언하고 관련 함수를 Bind 한다
	EndDelegate.BindUObject(this, &AODCharacterBase::ComboActionEnd); // 몽타주가 끝나면 호출할 함수를 지정해줍니다.
	AnimInstance->Montage_SetEndDelegate(EndDelegate, ComboActionMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer(); // 콤보타이머를 설정해줍니다.
}

void AODCharacterBase::ComboActionEnd(UAnimMontage* TargetMontage, bool IsPropertyEnded)
{
	ensure(CurrentCombo != 0); // 현재 콤보가 0이 절대로 나와서는 안되기때문에 체크합니다. // 인설션 함수로, 출력 로그에 에러를 발생합니다.
	CurrentCombo = 0; // 콤보를 초기화합니다.
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking); // 캐릭터의 이동모드를 다시 걷기로 지정해줍니다.

}

void AODCharacterBase::SetComboCheckTimer()
{
	// 콤보 인덱스를 지정해줍니다. (프레임정보,인덱스가 유효한지를 검사하기위해 DA를 참조한다)
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
	ComboTimerHandle.Invalidate(); // 타이머가 다시 호출되지 않도록 제거해줍니다. 

	if (HasNextComboCommand)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		//현재 콤보값은 우리가지정한 콤보값을 벗어나면 안되기 때문에  Clamp를 걸어줍니다.
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);

		//다음 세션에 대한 이름 정보를 가져옵니다. 이때는 스트링을 사용해야하기 때문에 Printf함수를 사용합니다. 
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
		AnimInstance->Montage_JumpToSection(NextSection, ComboActionMontage); // 해당 몽타주 섹션으로 바로 Jump합니다.
		SetComboCheckTimer(); // 콤보타이머를 다시 설정해줍니다.

		HasNextComboCommand = false; // 입력값을 초기화
	}
}


