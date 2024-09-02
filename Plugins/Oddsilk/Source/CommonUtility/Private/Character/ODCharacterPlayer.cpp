// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ODCharacterPlayer.h"
#include "Character/ODCharacterControlData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


AODCharacterPlayer::AODCharacterPlayer()
{
	//Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// 부착할때 특정 위치를 지정하지 않고, 소켓이라고 되어있는 특별한 이름 지시자를 지정해주면 스프링암의 끝에 자동으로 달라붙은다.
	//소켓의 이름은 SoketName에서 f12를 눌러서 직접 확인할 수 있다. -> SprintEndPoint
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	//Input 
	// 3인칭 템플릿의 값을 복사해서 사용하는 경우 IMC블루프린트에서 IA을 선택할때 경로를 확인해서 올바르게 다시 꼭 지정을 해줘야한다 그렇게 하지 않으면 올바르게 작동하지 않는다!!! 필수!!


	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Oddsilk/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputChangeActionControlRef(TEXT("/Script/EnhancedInput.InputAction'/Oddsilk/Input/Actions/IA_ChangeControl.IA_ChangeControl'"));
	if (nullptr != InputChangeActionControlRef.Object)
	{
		ChangeControlAction = InputChangeActionControlRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Oddsilk/Input/Actions/IA_ShoulderMove.IA_ShoulderMove'"));
	if (nullptr != InputActionShoulderMoveRef.Object)
	{
		ShoulderMoveAction = InputActionShoulderMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionShoulderLookRef(TEXT("/Script/EnhancedInput.InputAction'/Oddsilk/Input/Actions/IA_ShoulderLook.IA_ShoulderLook'"));
	if (nullptr != InputActionShoulderLookRef.Object)
	{
		ShoulderLookAction = InputActionShoulderLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionQuaterMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Oddsilk/Input/Actions/IA_QuaterMove.IA_QuaterMove'"));
	if (nullptr != InputActionQuaterMoveRef.Object)
	{
		QuaterMoveAction = InputActionQuaterMoveRef.Object;
	}

	CurrentCharacterControlType = ECharacterControlType::Quater;



	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Oddsilk/Input/Actions/IA_Attack.IA_Attack'"));
	if (nullptr != InputActionAttackRef.Object)
	{
		AttackAction = InputActionAttackRef.Object;
	}

}

void AODCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterControl(CurrentCharacterControlType); // Quater뷰가 초기 값이기때문에 Quater뷰로 시작하도록 설정합니다.
}


// 언리얼 엔진의 임력시스템에서, 입력액션과 우리가 선언한 Move와 Look함수를 서로 매핑시켜주는 것을 여기서 완료합니다. 
void AODCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));
	//EnhancedInputComponent를 사용하지 않는 만약의 경우가 있기때문에 CastChecked를 통해서 그런 경우 Error를 발생시키도록 합니다.
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &AODCharacterPlayer::ChangeCharacterControl);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &AODCharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &AODCharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &AODCharacterPlayer::QuaterMove);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AODCharacterPlayer::Attack);

}

void AODCharacterPlayer::ChangeCharacterControl()
{
	if (CurrentCharacterControlType == ECharacterControlType::Quater)
	{
		SetCharacterControl(ECharacterControlType::Shoulder);
	}
	else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
	{
		SetCharacterControl(ECharacterControlType::Quater);
	}
}

void AODCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	UODCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType]; // 상위 클래스에 선언된 맵데이터를 통해서 캐릭터 컨트롤 데이터를 가져옵니다.
	check(NewCharacterControl); // 반드시 존재해야하기 때문에 check함수를 사용해서 validation을 체크합니다.

	SetCharacterControlData(NewCharacterControl); // 캐릭터 컨트롤 데이터를 세팅해줍니다. 

	//새로운 캐릭터 컨트롤 데이터를 세팅해준 후에, EnhancedInputLocalPlayerSubsystem을 통해서 매핑컨텍스트를 추가해줍니다.
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController()); // 플레이어를 대상으로 설계된 전용 캐릭터클래스이기 때문에 CastChecked를 사용

	//subSystem이라고 하는 InputSystem을 가져와서 매핑 컨텍스트 에셋을 할당->정상적으로 할당되었을때 AddMappingContext를 통해서 매핑컨텍스트를 추가해줍니다.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			// SubSystem은 언제나 런타임에서 Remove 하거나 Add할 수 있습니다.
			Subsystem->AddMappingContext(NewMappingContext, 0);	// 우선선위를 지정해서 다양한 입력들이 서로 겹칠때도 우선순위가 높은 입력들에 대해서 액션들이 바인딩에서 수행할 수 있도록 지정
		}
	}
	// 여기까지 왔다면 문제없이 진행이 되었다는 것이기 때문에 현재의 DataType을 새로운 DataType으로 변경해줍니다.
	CurrentCharacterControlType = NewCharacterControlType;
}

void AODCharacterPlayer::SetCharacterControlData(const UODCharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation );
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

void AODCharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>(); //InputActionValue에서 우리가 XY값을 가져온 후에


	const  FRotator Rotation = Controller->GetControlRotation(); // Look함수에서 -> AddControllerYawInput, AddControllerPitchInput을 통해 업데이트된 컨트롤 로테이션 값을 가져와서
	const FRotator YawRotation(0, Rotation.Yaw, 0); // Yaw값만 따로 뺍니다
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 전진방향과
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 오른쪽 방향을 구합니다.


	//Movement 컴포넌트와 연결시켜서 실질적으로 캐릭터를 이동시켜 준다.
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

	// IA_Move에서 모디파이어를 지정할때 주의할 점 (Swizzle Input Axis Values)
	//		구체적인 축을 지정 = YXZ
	//		입력에서의 A,D =X축 값을 실제 캐릭터 이동에서는 Y축으로 변환을 하고, W,S = Y축 값을 실제 캐릭터 이동에서는 X축으로 변환을 해줘야한다. 
	//		- 이렇게 하면 입력값을 고려하지 않아도 논리적으로 많는 방향으로 코드를 작성할 수 있다
	//		- 만약 이렇게 하지 않는다면 위 AddMovementInput함수에서 X축과 Y축을 교차해야한다

}

void AODCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	//컨트롤러의 회전을 설정함으로써, 스프링 암이 해당 컨트롤러를 바라보도도록 설정합니다.
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
	// f12를 눌러서 해당 함수를 확인해보면, PlayerController의 포인터를 가져와서 AddYawInput값을 넣어주는 것을 확인할 수 있다
	//		그렇다면 PlayerController::AddYawInput은 어떻게 작동하는 것일까?
	//		RotationInput.Yaw회전값에 우리가 집어넣은 input값의 크기를 추가하고 있는 것을 확인할 수 있다. 
	//		-> RotationInput은 DeltaRot을 구축하는데에 사용되고, ViewRotation이라는 값에 DeltaRot이 기여를 해서 최종 ViewRotation값이 완성이 되면 SetControlRotation에 이 값을 집어넣어줍니다. 
	//			-> 결국SetControlRotation에서는 최종  ControlRotation이라는 속성을 우리가 지정한 Rotation 값으로 덮어 쓰는 것을 알 수 있다

	// ControllRotation 값은 언리얼 엔진의 콘솔 커맨드(단축키~)에서 확인할 수 있다 . 명령어 :: "DisplayAllPlayerControllerControlRotation" // DisplayAll->PlayerController->ControlRotation
}

void AODCharacterPlayer::QuaterMove(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>(); 

	float InputSizeSquared = MovementVector.SquaredLength();
	float MovementVectorSize = 1.0f;
	float MovementVectorSizeSquared = MovementVector.SquaredLength();
	
	//MovementVecter를 받아서 크기를 1로 정규화 시켜줍니다. 
	if (MovementVectorSizeSquared > 1.0f)
	{
		MovementVector.Normalize();
		MovementVectorSizeSquared = 1.0f;
	}
	else
	{
		MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
	}

	//  X와 Y 값을 inputAction의 모디파이어로 조절했었다. 그대로 사용하면 된다. 
	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);

	// controlRotation을 Forward방향으로 설정해주면 MovementComponent에서 지정한 옵션에 의해 캐릭터가 이동하는 방향으로 회전하게 됩니다.
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator()); 
	AddMovementInput(MoveDirection, MovementVectorSize);

}

void AODCharacterPlayer::Attack()
{
	ProcessComboCommand(); // CharacterBase의 몽타주 재생 함수를 상속받아서 Attack을 연결해줍니다. 


}
