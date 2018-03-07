// Harrison McGuire
// UE4 Version 4.18.3
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

#include "PickupAndRotateActor.h"
#include "GameFramework/Character.h"

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

	// FRotator MyRot = GetWorld()->GetFirstPlayerController()->GetControlRotation();

	// if (GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("My Rotation: %s"), *MyRot.ToString()));
	// } 

	// RotateActor(FQuat(MyRot));

	if(isHolding)
	{
		FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		FRotator PlayerRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
		ACharacter* OurPlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		
		TArray<USceneComponent*> Comps;
 
		OurPlayerCharacter->GetComponents(Comps);
		if(Comps.Num() > 0)
		{
			// USceneComponent* FoundComp = Comps[6]; good because it attaches it to the arms with the animations
			USceneComponent* FoundComp = Comps[7];
			//do stuff with FoundComp
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Comp Loc: %s"), *FoundComp->GetComponentLocation().ToString()));
			SetActorLocationAndRotation(FoundComp->GetComponentLocation(), FoundComp->GetComponentRotation());


		}

		// PlayerLocation.X += 20.0f;
		// PlayerLocation.Y -= 30.f;
		// PlayerLocation.Z += 30.f;
	}

}

void APickupAndRotateActor::RotateActor()
{
	FRotator MyRot = GetWorld()->GetFirstPlayerController()->GetControlRotation();

	SetActorRotation(FQuat(MyRot));
}

void APickupAndRotateActor::Pickup()
{
	isHolding = true;	
}

