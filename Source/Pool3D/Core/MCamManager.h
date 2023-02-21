// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCueBallBase.h"
#include "GameFramework/Pawn.h"
#include "MCamManager.generated.h"


class USpringArmComponent;
class UCameraComponent;
UCLASS()

class POOL3D_API AMCamManager : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
		UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
		TArray<FRotator> CameraPresetRotations;
	UPROPERTY(BlueprintReadOnly)
		int CurrentCameraRotationIndex;
	UPROPERTY(EditAnywhere)
		int ShotForceConst = 15000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMCueBallBase* CueBallObj;


public:
	// Sets default values for this pawn's properties
	AMCamManager();
	virtual void Tick(float DeltaTime) override;
	void CameraViewUpdate();
	void OnTouchSwipe();
	void TouchPressed(ETouchIndex::Type TouchType, FVector NewTouchLocation);
	void TouchReleased(ETouchIndex::Type TouchType, FVector ReleasedTouchLocation);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bTouchInitiated;
	bool bShotInitiated;
	FVector ShotStartLocation;
	FVector ShotEndLocation;



};
