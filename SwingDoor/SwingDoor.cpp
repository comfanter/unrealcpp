// Harrison McGuire 
// UE4 Version 4.18.2 
// https://github.com/Harrison1/unrealcpp 
// https://severallevels.io 
// https://harrisonmcguire.com
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/FTimerManager/SetTimer/4/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/AActor/SetActorRelativeRotation/2/index.html
// WIP

#include "SwingDoor.h"
// add constructor header
#include "ConstructorHelpers.h"
#include "TimerManager.h"

// Sets default values
ASwingDoor::ASwingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
    RootComponent = Door;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("/Game/StarterContent/Props/SM_Door.SM_Door"));

	if (DoorAsset.Succeeded())
    {
        Door->SetStaticMesh(DoorAsset.Object);
        Door->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        Door->SetWorldScale3D(FVector(1.f));
	}

	isOpen = false;
}

// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		float CurrentRotation = GetActorRotation().Yaw;

		if(!isOpen && !FMath::IsNearlyEqual(CurrentRotation, 90.0f, 0.5f))
		{
			CurrentRotation += DeltaTime*50;
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("rotation: %f"), CurrentRotation));
			CurrentRotation = FMath::Clamp(CurrentRotation, 0.0f, 90.0f);
			FRotator NewRotation = FRotator(0.0f, CurrentRotation, 0.0f);
			SetActorRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);

		}

		if(FMath::IsNearlyEqual(CurrentRotation, 90.0f, 0.5f)) 
		{
			isOpen = true;
		}
	}

}

void ASwingDoor::SwingOpen()
{
	GLog->Log("Open Door");

	isOpen = false;
}

