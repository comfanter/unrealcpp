// Harrison McGuire
// UE4 Version 4.18.3
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

#include "PickupAndRotateActor.h"


// Sets default values
APickupAndRotateActor::APickupAndRotateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	RootComponent = MyMesh;

}

// Called when the game starts or when spawned
void APickupAndRotateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupAndRotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator MyRot = GetWorld()->GetFirstPlayerController()->GetControlRotation();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("My Rotation: %s"), *MyRot.ToString()));
	} 

	RotateActor(FQuat(MyRot));

}

void APickupAndRotateActor::RotateActor(FQuat NewRotation)
{
	SetActorRotation(NewRotation);
}

