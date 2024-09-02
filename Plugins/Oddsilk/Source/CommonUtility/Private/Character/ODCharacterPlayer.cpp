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
	// �����Ҷ� Ư�� ��ġ�� �������� �ʰ�, �����̶�� �Ǿ��ִ� Ư���� �̸� �����ڸ� �������ָ� ���������� ���� �ڵ����� �޶������.
	//������ �̸��� SoketName���� f12�� ������ ���� Ȯ���� �� �ִ�. -> SprintEndPoint
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	//Input 
	// 3��Ī ���ø��� ���� �����ؼ� ����ϴ� ��� IMC�������Ʈ���� IA�� �����Ҷ� ��θ� Ȯ���ؼ� �ùٸ��� �ٽ� �� ������ ������Ѵ� �׷��� ���� ������ �ùٸ��� �۵����� �ʴ´�!!! �ʼ�!!


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

	SetCharacterControl(CurrentCharacterControlType); // Quater�䰡 �ʱ� ���̱⶧���� Quater��� �����ϵ��� �����մϴ�.
}


// �𸮾� ������ �ӷ½ý��ۿ���, �Է¾׼ǰ� �츮�� ������ Move�� Look�Լ��� ���� ���ν����ִ� ���� ���⼭ �Ϸ��մϴ�. 
void AODCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));
	//EnhancedInputComponent�� ������� �ʴ� ������ ��찡 �ֱ⶧���� CastChecked�� ���ؼ� �׷� ��� Error�� �߻���Ű���� �մϴ�.
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
	UODCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType]; // ���� Ŭ������ ����� �ʵ����͸� ���ؼ� ĳ���� ��Ʈ�� �����͸� �����ɴϴ�.
	check(NewCharacterControl); // �ݵ�� �����ؾ��ϱ� ������ check�Լ��� ����ؼ� validation�� üũ�մϴ�.

	SetCharacterControlData(NewCharacterControl); // ĳ���� ��Ʈ�� �����͸� �������ݴϴ�. 

	//���ο� ĳ���� ��Ʈ�� �����͸� �������� �Ŀ�, EnhancedInputLocalPlayerSubsystem�� ���ؼ� �������ؽ�Ʈ�� �߰����ݴϴ�.
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController()); // �÷��̾ ������� ����� ���� ĳ����Ŭ�����̱� ������ CastChecked�� ���

	//subSystem�̶�� �ϴ� InputSystem�� �����ͼ� ���� ���ؽ�Ʈ ������ �Ҵ�->���������� �Ҵ�Ǿ����� AddMappingContext�� ���ؼ� �������ؽ�Ʈ�� �߰����ݴϴ�.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			// SubSystem�� ������ ��Ÿ�ӿ��� Remove �ϰų� Add�� �� �ֽ��ϴ�.
			Subsystem->AddMappingContext(NewMappingContext, 0);	// �켱������ �����ؼ� �پ��� �Էµ��� ���� ��ĥ���� �켱������ ���� �Էµ鿡 ���ؼ� �׼ǵ��� ���ε����� ������ �� �ֵ��� ����
		}
	}
	// ������� �Դٸ� �������� ������ �Ǿ��ٴ� ���̱� ������ ������ DataType�� ���ο� DataType���� �������ݴϴ�.
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
	FVector2D MovementVector = Value.Get<FVector2D>(); //InputActionValue���� �츮�� XY���� ������ �Ŀ�


	const  FRotator Rotation = Controller->GetControlRotation(); // Look�Լ����� -> AddControllerYawInput, AddControllerPitchInput�� ���� ������Ʈ�� ��Ʈ�� �����̼� ���� �����ͼ�
	const FRotator YawRotation(0, Rotation.Yaw, 0); // Yaw���� ���� ���ϴ�
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // ���������
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // ������ ������ ���մϴ�.


	//Movement ������Ʈ�� ������Ѽ� ���������� ĳ���͸� �̵����� �ش�.
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

	// IA_Move���� ������̾ �����Ҷ� ������ �� (Swizzle Input Axis Values)
	//		��ü���� ���� ���� = YXZ
	//		�Է¿����� A,D =X�� ���� ���� ĳ���� �̵������� Y������ ��ȯ�� �ϰ�, W,S = Y�� ���� ���� ĳ���� �̵������� X������ ��ȯ�� ������Ѵ�. 
	//		- �̷��� �ϸ� �Է°��� ������� �ʾƵ� �������� ���� �������� �ڵ带 �ۼ��� �� �ִ�
	//		- ���� �̷��� ���� �ʴ´ٸ� �� AddMovementInput�Լ����� X��� Y���� �����ؾ��Ѵ�

}

void AODCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	//��Ʈ�ѷ��� ȸ���� ���������ν�, ������ ���� �ش� ��Ʈ�ѷ��� �ٶ󺸵����� �����մϴ�.
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
	// f12�� ������ �ش� �Լ��� Ȯ���غ���, PlayerController�� �����͸� �����ͼ� AddYawInput���� �־��ִ� ���� Ȯ���� �� �ִ�
	//		�׷��ٸ� PlayerController::AddYawInput�� ��� �۵��ϴ� ���ϱ�?
	//		RotationInput.Yawȸ������ �츮�� ������� input���� ũ�⸦ �߰��ϰ� �ִ� ���� Ȯ���� �� �ִ�. 
	//		-> RotationInput�� DeltaRot�� �����ϴµ��� ���ǰ�, ViewRotation�̶�� ���� DeltaRot�� �⿩�� �ؼ� ���� ViewRotation���� �ϼ��� �Ǹ� SetControlRotation�� �� ���� ����־��ݴϴ�. 
	//			-> �ᱹSetControlRotation������ ����  ControlRotation�̶�� �Ӽ��� �츮�� ������ Rotation ������ ���� ���� ���� �� �� �ִ�

	// ControllRotation ���� �𸮾� ������ �ܼ� Ŀ�ǵ�(����Ű~)���� Ȯ���� �� �ִ� . ��ɾ� :: "DisplayAllPlayerControllerControlRotation" // DisplayAll->PlayerController->ControlRotation
}

void AODCharacterPlayer::QuaterMove(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>(); 

	float InputSizeSquared = MovementVector.SquaredLength();
	float MovementVectorSize = 1.0f;
	float MovementVectorSizeSquared = MovementVector.SquaredLength();
	
	//MovementVecter�� �޾Ƽ� ũ�⸦ 1�� ����ȭ �����ݴϴ�. 
	if (MovementVectorSizeSquared > 1.0f)
	{
		MovementVector.Normalize();
		MovementVectorSizeSquared = 1.0f;
	}
	else
	{
		MovementVectorSize = FMath::Sqrt(MovementVectorSizeSquared);
	}

	//  X�� Y ���� inputAction�� ������̾�� �����߾���. �״�� ����ϸ� �ȴ�. 
	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);

	// controlRotation�� Forward�������� �������ָ� MovementComponent���� ������ �ɼǿ� ���� ĳ���Ͱ� �̵��ϴ� �������� ȸ���ϰ� �˴ϴ�.
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator()); 
	AddMovementInput(MoveDirection, MovementVectorSize);

}

void AODCharacterPlayer::Attack()
{
	ProcessComboCommand(); // CharacterBase�� ��Ÿ�� ��� �Լ��� ��ӹ޾Ƽ� Attack�� �������ݴϴ�. 


}
