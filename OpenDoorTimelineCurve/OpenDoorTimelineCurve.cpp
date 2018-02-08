// Harrison McGuire
// UE4 Version 4.18.3
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

// helpful links
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/FTimeline/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/USceneComponent/index.html
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/UPrimitiveComponent/OnComponentBeginOverlap/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/UPrimitiveComponent/OnComponentEndOverlap/
// https://docs.unrealengine.com/latest/INT/BlueprintAPI/Math/Vector/UnrotateVector/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Kismet/UKismetMathLibrary/LessLess_VectorRotator/index.html
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Kismet/UKismetMathLibrary/index.html

#include "OpenDoorTimelineCurve.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AOpenDoorTimelineCurve::AOpenDoorTimelineCurve()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Open = false;

    MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));
    MyBoxComponent->InitBoxExtent(FVector(50,50,50));
    RootComponent = MyBoxComponent;

    Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
    Door->SetRelativeLocation(FVector(0.0f, 50.0f, -50.0f));
    Door->SetupAttachment(RootComponent);

    MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AOpenDoorTimelineCurve::OnOverlapBegin);
    MyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &AOpenDoorTimelineCurve::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AOpenDoorTimelineCurve::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOpenDoorTimelineCurve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(Open)
    {
        // FVector MyLoc = GetActorLocation();
        // FVector TargetLoc = FVector(0,0,90);
        // FVector Dir = (TargetLoc - MyLoc);
        // Dir.Normalize();

        

        // FRotator NewRot = FRotator(Door->GetComponentRotation().Pitch, Door->GetComponentRotation().Yaw, 90.0f);
        FVector RotNew = FVector(0, RotateValue, 0);
        RotNew.Normalize();
        Door->SetRelativeRotation(FMath::Lerp(Door->GetComponentRotation(), RotNew.Rotation(), 0.01f));
        
    } 
    else if (!FMath::IsNearlyEqual(Door->GetComponentRotation().Yaw, 0.0f, 1.5f))
    {
        // FRotator NewRot = FRotator(Door->GetComponentRotation().Pitch, Door->GetComponentRotation().Yaw, 0.0f);
        FVector RotNewR = FVector(0, 0, 0);
        RotNewR.Normalize();
        Door->SetRelativeRotation(FMath::Lerp(Door->GetComponentRotation(), RotNewR.Rotation(), 0.01f));
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
    
    // Open = !Open;

	// FVector MyLoc = GetActorLocation();
    // FVector TargetLoc = FVector(0,0,90);
    // FVector Dir = (TargetLoc - MyLoc);
    // Dir.Normalize();
    // FVector RotNew = FVector(0, 90, 0);
    // FRotator NewRot = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, 90.0f);
    // SetActorRotation(FMath::Lerp(GetActorRotation(),RotNew.Rotation(),MyCurveFloat));
}

void AOpenDoorTimelineCurve::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if ( (OtherActor != nullptr ) && (OtherActor != this) && ( OtherComp != nullptr ) ) 
    {
        FVector PawnLocation = OtherActor->GetActorLocation();
        FVector Direction = GetActorLocation() - PawnLocation;
        // float Value = 90.0f;
        // if(Direction)
        FVector Dir = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

        if(Dir.X > 0.0f)
        {
            RotateValue = 90.0f;
        }
        else
        {
            RotateValue = -90.0f;
        }

        Open = true;
    }
}

void AOpenDoorTimelineCurve::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if ( (OtherActor != nullptr ) && (OtherActor != this) && ( OtherComp != nullptr ) )  
    {
        Open = false;
    }
}