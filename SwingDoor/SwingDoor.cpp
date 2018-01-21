// Harrison McGuire 
// UE4 Version 4.18.2 
// https://github.com/Harrison1/unrealcpp 
// https://severallevels.io 
// https://harrisonmcguire.com
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/FTimerManager/SetTimer/4/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/AActor/SetActorRelativeRotation/2/index.html
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/USceneComponent/GetComponentRotation/index.html
// WIP

#include "SwingDoor.h"
// add constructor header
#include "ConstructorHelpers.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASwingDoor::ASwingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	BoxComp->InitBoxExtent(FVector(150,100,100));
	BoxComp->SetCollisionProfileName("Trigger");
	RootComponent = BoxComp;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
    Door->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("/Game/StarterContent/Props/SM_Door.SM_Door"));

	if (DoorAsset.Succeeded())
    {
        Door->SetStaticMesh(DoorAsset.Object);
        Door->SetRelativeLocation(FVector(0.0f, 50.0f, -100.0f));
        Door->SetWorldScale3D(FVector(1.f));
	}



	isOpen = false;
	isClosed = true;

	Opening = false;
	Closing = false;
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

	DrawDebugBox(GetWorld(), BoxComp->GetComponentLocation(), BoxComp->GetScaledBoxExtent(), FColor::Turquoise, false, -1, 0, 5);

	if(Opening) 
	{
		OpenDoor(DeltaTime);
	}

	if(Closing)
	{
		CloseDoor(DeltaTime);
	}

}

void ASwingDoor::OpenDoor(float dt)
{
	// GLog->Log("Opening Door");

	float CurrentRotation = Door->GetComponentRotation().Yaw;

	if(Opening && !FMath::IsNearlyEqual(CurrentRotation, 90.0f, 0.5f))
	{
		// CurrentRotation += dt*50;
		float AddRot = dt*50;
		// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("rotation: %f"), CurrentRotation));
		// CurrentRotation = FMath::Clamp(CurrentRotation, 0.0f, 90.0f);
		FRotator NewRotation = FRotator(0.0f, AddRot, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);

	}

	if(FMath::IsNearlyEqual(CurrentRotation, 90.0f, 0.5f)) 
	{

		Closing = false;
		Opening = false;
	}
}

void ASwingDoor::CloseDoor(float dt)
{
	// GLog->Log("Closing Door");

	float CurrentRotation = Door->GetComponentRotation().Yaw;

	if(Closing && !FMath::IsNearlyEqual(CurrentRotation, 0.0f, 0.5f))
	{
		// CurrentRotation -= dt*50;
		// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("rotation: %f"), CurrentRotation));
		// CurrentRotation = FMath::Clamp(CurrentRotation, 0.0f, 90.0f);
		float MinusRot = -dt*50;
		FRotator NewRotation = FRotator(0.0f, MinusRot, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);

	}

	if(FMath::IsNearlyEqual(CurrentRotation, 0.0f, 0.5f)) 
	{
		Closing = false;
		Opening = false;
	}
}

void ASwingDoor::ToggleDoor() 
{
	GLog->Log("Toggle This Door");

	UE_LOG(LogTemp,Warning,TEXT("Door FV: %s"), *Door->GetForwardVector().ToString());
	
	if(isClosed) {
		isClosed = false;
		Closing = false;
		isOpen = true;
		Opening = true;
	} else {
		isOpen = false;
		Opening = false;
		isClosed = true;
		Closing = true;
	}
	
}