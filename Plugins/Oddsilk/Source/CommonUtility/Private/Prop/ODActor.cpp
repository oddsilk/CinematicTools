// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ODActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AODActor::AODActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// header���� ������ �����͵��� ���� �����ؼ� �⺻������ �����Ѵ�.
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body")); // ���� Ȯ���� ������ؼ� include// �Լ� ���ڿ� TEXT�� �־� �̸��� �������� �� �ִ�
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water")); // �̸��� �����ؾ��Ѵ�. ���� �̸��� ������ �� ����.


	// RootComponent�� �������� �ݵ�� ������ ������մϴ�. 
	RootComponent = Body;
	Water->SetupAttachment(Body); // RootComponent�� Body�̱� ������ Body�� Water�� �������ݴϴ�.
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f));


	static::ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Oddsilk/StaticMesh/SM_FountahinBody.SM_FountahinBody"));
	if (BodyMeshRef.Object)
	{
		Body->SetStaticMesh(BodyMeshRef.Object);
	}
	static::ConstructorHelpers::FObjectFinder<UStaticMesh>WaterMeshRef(TEXT("/Oddsilk/StaticMesh/SM_FountainWater.SM_FountainWater"));
	if (WaterMeshRef.Object)
	{
		Water->SetStaticMesh(WaterMeshRef.Object);
	}


}

// Called when the game starts or when spawned
void AODActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AODActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

