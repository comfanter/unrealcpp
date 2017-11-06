// Harrison McGuire UE4
// Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#include "MyDrawDebugHelpers.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMyDrawDebugHelpers::AMyDrawDebugHelpers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// init variables with values
	LocationOne = FVector(0,0,600);
	LocationTwo = FVector(0,-600,600);
	LocationThree = FVector(0,600,600);

}

// Called when the game starts or when spawned
void AMyDrawDebugHelpers::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugPoint(GetWorld(), LocationOne, 200, FColor(52,220,239), true);

	DrawDebugSphere(GetWorld(), LocationTwo, 200, 26, FColor(181,0,0), true);

	DrawDebugSphere(GetWorld(), LocationThree, 200, 26, FColor(0,104,167), true);
	
}

// Called every frame
void AMyDrawDebugHelpers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

