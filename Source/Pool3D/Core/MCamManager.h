// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	// Sets default values for this pawn's properties
	AMCamManager();
	
	virtual void Tick(float DeltaTime) override;
	void CameraViewUpdate();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
