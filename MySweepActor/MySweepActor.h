// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySweepActor.generated.h"

UCLASS()
class UNREALCPP_API AMySweepActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySweepActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Sweeping")
	float SphereHeight = 200;

	UPROPERTY(EditAnywhere, Category = "Sweeping")
	float SphereRadius = 500;

	UPROPERTY(EditAnywhere, Category = "Sweeping")
	int32 Segments = 100;

	UPROPERTY(EditAnywhere, Category = "Sweeping")
	FVector DLocation;

	
};
