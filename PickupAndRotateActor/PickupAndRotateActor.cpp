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

	ACharacter* OurPlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	TArray<USceneComponent*> Components;
 
	OurPlayerCharacter->GetComponents(Components);

	if(Components.Num() > 0)
	{
		for (auto& Comp : Components)
		{
			if(Comp->GetName() == "HoldingComponent")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	}
}

// Called every frame
void APickupAndRotateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isHolding && HoldingComp)
	{
		SetActorLocationAndRotation(HoldingComp->GetComponentLocation(), HoldingComp->GetComponentRotation());
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

