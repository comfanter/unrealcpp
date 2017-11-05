// Harrison McGuire UE4 Version 4.18 https://github.com/Harrison1/unrealcpp https://severallevels.io

#include "RotateActorAroundWithUpVector.h"


// Sets default values
ARotateActorAroundWithUpVector::ARotateActorAroundWithUpVector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotateActorAroundWithUpVector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotateActorAroundWithUpVector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	FVector NewLocation = FVector (0,0,800);

	FVector SNew = FVector(XValue,YValue,ZValue);

	AngleAxis += PlusBy;

	if(AngleAxis > 360.0f) {

		AngleAxis = 1;
	}

	FVector RotateValue = SNew.RotateAngleAxis(AngleAxis, FVector (FXValue,FYValue,FZValue));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Up Vector: %s"), *GetActorUpVector().ToString()));	

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	FRotator NewRotation = FRotator(0, AngleAxis, 0);
	
	FQuat QuatRotation = FQuat(NewRotation);
	
	// AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);


	SetActorLocationAndRotation(NewLocation, QuatRotation, false, 0, ETeleportType::None);

}

