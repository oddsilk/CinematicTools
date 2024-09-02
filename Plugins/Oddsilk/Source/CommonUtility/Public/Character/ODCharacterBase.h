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
	// 입력, 플레이어와 관련된 기본기능과, 불필요한 함수들은 제거해버린다, 
protected:
	virtual void SetCharacterControlData(const class UODCharacterControlData* CharacterControlData);

	//해당 Enum을 바탕으로 두가지 에셋 오브젝트를 바로 얻어 올 수 있도록 Map데이터를 하나 선언한다.
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
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsPropertyEnded ); // 몽타주에 설정된 델리게이트를 통해서 바로 호출 할 수 있도록 맞춰주겠다.
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = false; // 내부로직에서만 사용할 것이기 때문에 UPROPERTY를 사용하지 않는다.// 그래서 지난번처럼 intager로 선언할 필요가 없다
};
