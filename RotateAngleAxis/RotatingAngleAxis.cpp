// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#include "RotatingAngleAxis.h"

// Sets default values
ARotatingAngleAxis::ARotatingAngleAxis()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotatingAngleAxis::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ARotatingAngleAxis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewActorLocation = GetActorLocation().RotateAngleAxis(1.0f, FVector (XValue,YValue,ZValue));
	
	SetActorLocation(NewActorLocation);
	
}