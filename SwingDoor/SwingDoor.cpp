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

}

// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ASwingDoor::SwingOpen, 2.0f);
	
}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwingDoor::SwingOpen()
{
	GLog->Log("Open Door");
	
	FQuat QuatRotation = FQuat(FRotator(0, 90, 0));
	
	SetActorRelativeRotation(QuatRotation, false, 0, ETeleportType::None);
}

