
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MBallBase.generated.h"

UCLASS()
class POOL3D_API AMBallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMBallBase();

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SM_Ball;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
