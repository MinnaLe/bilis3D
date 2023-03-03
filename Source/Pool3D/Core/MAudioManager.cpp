// Fill out your copyright notice in the Description page of Project Settings.


#include "MAudioManager.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AMAudioManager::AMAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CrSoundCue = Cast<USoundWave>(StaticLoadObject(USoundWave::StaticClass(), NULL, TEXT("SoundWave'/Game/Assets/Audio/birds.birds'")));
}

// Called when the game starts or when spawned
void AMAudioManager::BeginPlay()
{
	Super::BeginPlay();
	if (CrSoundCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), CrSoundCue);
	}
}

// Called every frame
void AMAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

