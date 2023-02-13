// Fill out your copyright notice in the Description page of Project Settings.


#include "MBallBase.h"

// Sets default values
AMBallBase::AMBallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Ball"));
	SM_Ball->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
	UStaticMesh* ballMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/Assets/StaticMeshes/poolBall.poolBall'")));

	if (ballMesh)
	{
		SM_Ball->SetStaticMesh(ballMesh);
	}

	RootComponent = SM_Ball;
	SM_Ball->SetSimulatePhysics(true);
	SM_Ball->SetMassOverrideInKg(NAME_None, 0.21);
	SM_Ball->SetLinearDamping(0.01);
	SM_Ball->SetAngularDamping(0.5);




}

// Called when the game starts or when spawned
void AMBallBase::BeginPlay()
{
	Super::BeginPlay();


	
}



void AMBallBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}


// Called every frame
void AMBallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

