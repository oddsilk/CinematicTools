// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ODActor.generated.h"

UCLASS()
class COMMONUTILITY_API AODActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AODActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh) // ��üŸ�� Visible
	TObjectPtr<class UStaticMeshComponent> Body; // class ���漱������ Header �������� ����

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh) 
	TObjectPtr<class UStaticMeshComponent> Water; 

};
