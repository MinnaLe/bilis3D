// Fill out your copyright notice in the Description page of Project Settings.


#include "MCamManager.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
//using namespace AMCamManager;


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
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	
}

void AMCamManager::CameraViewUpdate()
{
	CurrentCameraRotationIndex =( CurrentCameraRotationIndex + 1)% (CameraPresetRotations.Num());
	SetActorRotation(CameraPresetRotations[CurrentCameraRotationIndex]);
	UE_LOG(LogTemp, Warning, TEXT("Choosen index %d"), CurrentCameraRotationIndex);
}


void AMCamManager::OnTouchSwipe()
{
	if (bShotInitiated)
	{
	FHitResult HitResult;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);
	FVector endLocation = HitResult.Location;
	endLocation.Z = CueBallObj->GetActorLocation().Z;

	FHitResult SphereHitResult;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), ShotStartLocation, endLocation, 1.3f, ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>{CueBallObj},
		EDrawDebugTrace::ForOneFrame, SphereHitResult, true);
	ShotEndLocation = SphereHitResult.Location;
	}
}




// Called every frame
void AMCamManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bTouchInitiated)
		OnTouchSwipe();
}

void AMCamManager::TouchPressed(ETouchIndex::Type TouchType, FVector NewTouchLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Touch pressed"));
	bTouchInitiated = true;
	FHitResult HitResult;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);
	if (Cast<AMCueBallBase>(HitResult.GetActor()))
	{
		ShotStartLocation = HitResult.Location;
		bShotInitiated = true;
	}

}

void AMCamManager::TouchReleased(ETouchIndex::Type TouchType, FVector ReleasedTouchLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Touch released"));
	bTouchInitiated = false;
	if (bShotInitiated)
	{
		FVector Force = (ShotEndLocation - ShotStartLocation);
		UKismetMathLibrary::Vector_Normalize(Force);
		CueBallObj->SM_Ball->AddForce(Force * ShotForceConst, NAME_None, true);
		bShotInitiated = false;
	}
}




// Called to bind functionality to input
void AMCamManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("CameraViewChange"), EInputEvent::IE_Pressed, this, &AMCamManager::CameraViewUpdate);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMCamManager::TouchPressed);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AMCamManager::TouchReleased);

}

