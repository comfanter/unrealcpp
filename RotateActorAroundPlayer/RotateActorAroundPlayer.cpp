// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#include "RotateActorAroundPlayer.h"


// Sets default values
ARotateActorAroundPlayer::ARotateActorAroundPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// init values
	XValue = 300.f;
	FZValue = 1.f;
	PlusBy = 1.f;
}

// Called when the game starts or when spawned
void ARotateActorAroundPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotateActorAroundPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		
	FVector Dimensions = FVector(XValue,YValue,ZValue);
	
	AngleAxis += PlusBy;

	if(AngleAxis > 360.0f) {

		AngleAxis = 1;
	}

	FVector myCharacter = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector RotateValue = Dimensions.RotateAngleAxis(AngleAxis, FVector (FXValue,FYValue,FZValue));

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;

	SetActorLocation(NewLocation, false, 0, ETeleportType::None);

}

