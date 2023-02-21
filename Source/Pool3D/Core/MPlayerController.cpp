// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerController.h"

void AMPlayerController::BeginPlay()
{
		Super::BeginPlay();
		this->SetShowMouseCursor(true);
}