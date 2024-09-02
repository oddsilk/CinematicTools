// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ODCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};


UCLASS()
class COMMONUTILITY_API AODCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AODCharacterBase();
	// �Է�, �÷��̾�� ���õ� �⺻��ɰ�, ���ʿ��� �Լ����� �����ع�����, 
protected:
	virtual void SetCharacterControlData(const class UODCharacterControlData* CharacterControlData);

	//�ش� Enum�� �������� �ΰ��� ���� ������Ʈ�� �ٷ� ��� �� �� �ֵ��� Map�����͸� �ϳ� �����Ѵ�.
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UODCharacterControlData*> CharacterControlManager;

//ComboActionSection
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UODComboActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded ); // ��Ÿ�ֿ� ������ ��������Ʈ�� ���ؼ� �ٷ� ȣ�� �� �� �ֵ��� �����ְڴ�.
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false; // ���η��������� ����� ���̱� ������ UPROPERTY�� ������� �ʴ´�.// �׷��� ������ó�� intager�� ������ �ʿ䰡 ����
};
