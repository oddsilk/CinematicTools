// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ODActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AODActor::AODActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// header에서 선언한 포인터들을 직접 생성해서 기본값으로 부착한다.
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body")); // 이제 확정을 지어야해서 include// 함수 인자에 TEXT를 넣어 이름을 지정해줄 수 있다
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water")); // 이름은 고유해야한다. 같은 이름을 지어줄 수 없다.


	// RootComponent가 무엇인지 반드시 지정을 해줘야합니다. 
	RootComponent = Body;
	Water->SetupAttachment(Body); // RootComponent가 Body이기 때문에 Body에 Water를 부착해줍니다.
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

