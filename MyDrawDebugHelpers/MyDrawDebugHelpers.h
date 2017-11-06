// Harrison McGuire UE4
// Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDrawDebugHelpers.generated.h"

UCLASS()
class UNREALCPP_API AMyDrawDebugHelpers : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDrawDebugHelpers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// declare location variables
	UPROPERTY(EditAnywhere, Category = "Locations")
	FVector LocationOne;

	UPROPERTY(EditAnywhere, Category = "Locations")
	FVector LocationTwo;

	UPROPERTY(EditAnywhere, Category = "Locations")
	FVector LocationThree;
	
};
