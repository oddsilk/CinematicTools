// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ODComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class COMMONUTILITY_API UODComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UODComboActionData();

	UPROPERTY(EditAnywhere, Category = Name)
	FString MontageSectionNamePrefix; // ��Ÿ�� �����̸�

	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount; // �ִ� �޺� ī��Ʈ


	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate; // �������� ����ӵ� 
	
	UPROPERTY(EditAnywhere, Category = Name)
	TArray<float> EffectiveFrameCount; //�Է��� �����ϴ� �������� ����
};
