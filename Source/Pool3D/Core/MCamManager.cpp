// Fill out your copyright notice in the Description page of Project Settings.


#include "MCamManager.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMCamManager::AMCamManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SceneRoot->SetupAttachment(RootComponent);
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SceneRoot);
	SpringArmComponent->TargetArmLength = 100;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraPresetRotations = {FRotator(-90, -60, 0),FRotator(-120 ,-60, 0),FRotator(-70, -60, 10),};
	//CameraPresetRotations = { FRotator(0,-60,-90),FRotator(0,-60,-120),FRotator(10,-60, -70), };

}

// Called when the game starts or when spawned
void AMCamManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMCamManager::CameraViewUpdate()
{
	CurrentCameraRotationIndex =( CurrentCameraRotationIndex + 1)% (CameraPresetRotations.Num());
	SetActorRotation(CameraPresetRotations[CurrentCameraRotationIndex]);
	UE_LOG(LogTemp, Warning, TEXT("Choosen index %d"), CurrentCameraRotationIndex);
}






// Called every frame
void AMCamManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMCamManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("CameraViewChange"), EInputEvent::IE_Pressed, this, &AMCamManager::CameraViewUpdate);
}

