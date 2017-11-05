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

	FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// FVector MyLocation = FVector (0,0,800);

	FVector SNew = FVector(XValue,YValue,ZValue);

	// NewLocation.X += XValue;
	// NewLocation.Y += YValue;
	// NewLocation.Z += ZValue;

	AngleAxis += PlusBy;

	if(AngleAxis > 360.0f) {

		AngleAxis = 1;
	}

	FVector myCharacter = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	int32 mynumpawns = GetWorld()->GetNumPawns();
	// myCharacter->GetActorLocation();

	FVector RotateValue = SNew.RotateAngleAxis(AngleAxis, FVector (FXValue,FYValue,FZValue));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("RotateValue: %s"), *RotateValue.ToString()));	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("AngleAxis: %f"), AngleAxis));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Location: %s"), *myCharacter.ToString()));	

	NewLocation.X += RotateValue.X;
	NewLocation.Y += RotateValue.Y;
	NewLocation.Z += RotateValue.Z;
	
	SetActorLocation(NewLocation);

	// SetActorRelativeLocation(NewActorLocation, false, 0, ETeleportType::None);
	
}