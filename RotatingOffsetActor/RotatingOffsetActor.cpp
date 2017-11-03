// Harrison McGuire UE4 Version 4.18 https://github.com/Harrison1/unrealcpp https://severallevels.io/

#include "RotatingOffsetActor.h"


// Sets default values
ARotatingOffsetActor::ARotatingOffsetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotatingOffsetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingOffsetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// rotate and offset actor
	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);
	FVector NewLocation = FVector(XValue, YValue, ZValue);
	
	FQuat QuatRotation = FQuat(NewRotation);
	
	AddActorLocalOffset(NewLocation, false, 0, ETeleportType::None);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
	
}

