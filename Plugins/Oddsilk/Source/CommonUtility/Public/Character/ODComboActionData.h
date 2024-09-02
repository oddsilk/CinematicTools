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
	FString MontageSectionNamePrefix; // 몽타주 섹션이름

	UPROPERTY(EditAnywhere, Category = Name)
	uint8 MaxComboCount; // 최대 콤보 카운트


	UPROPERTY(EditAnywhere, Category = Name)
	float FrameRate; // 프레임의 재생속도 
	
	UPROPERTY(EditAnywhere, Category = Name)
	TArray<float> EffectiveFrameCount; //입력을 감지하는 프레임의 기준
};
