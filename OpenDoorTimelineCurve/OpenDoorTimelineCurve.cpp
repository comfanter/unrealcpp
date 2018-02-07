// Harrison McGuire
// UE4 Version 4.18.3
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

// helpful links
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/FTimeline/

#include "OpenDoorTimelineCurve.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOpenDoorTimelineCurve::AOpenDoorTimelineCurve()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Open = false;

    MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
    RootComponent = MyBoxComponent;

    MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
    MyMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AOpenDoorTimelineCurve::BeginPlay()
{
	Super::BeginPlay();

    OpenDoor();

}

// Called every frame
void AOpenDoorTimelineCurve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(Open)
    {
        FVector MyLoc = GetActorLocation();
        FVector TargetLoc = FVector(0,0,90);
        FVector Dir = (TargetLoc - MyLoc);
        Dir.Normalize();
        FVector RotNew = FVector(0, 90, 0);
        FRotator NewRot = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 90.0f);
        SetActorRotation(FMath::Lerp(GetActorRotation(),RotNew.Rotation(),0.01f));
    }

}

void AOpenDoorTimelineCurve::OpenDoor()
{

    // Alternative Method: Include Gameplay statics, find the first player pawn and get the location.
	// APawn* OurPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    // FVector Loc = OurPlayerPawn->GetActorLocation();

    // get first player pawn location
	FVector MyCharacterLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// screen log player location
    if (GEngine) 
    { 
	    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Location: %s"), *MyCharacterLocation.ToString()));
    }
    
    Open = !Open;

	// FVector MyLoc = GetActorLocation();
    // FVector TargetLoc = FVector(0,0,90);
    // FVector Dir = (TargetLoc - MyLoc);
    // Dir.Normalize();
    // FVector RotNew = FVector(0, 90, 0);
    // FRotator NewRot = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 90.0f);
    // SetActorRotation(FMath::Lerp(GetActorRotation(),RotNew.Rotation(),MyCurveFloat));
}
