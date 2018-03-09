// Harrison McGuire
// UE4 Version 4.18.3
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

#include "PickupAndRotateActor.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

// Sets default values
APickupAndRotateActor::APickupAndRotateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	RootComponent = MyMesh;

	isHolding = false;
	isGravity = true;

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
	isHolding = !isHolding;	
	isGravity = !isGravity;
	MyMesh->SetEnableGravity(isGravity);
	MyMesh->SetSimulatePhysics(isHolding ? false : true);
	MyMesh->SetCollisionEnabled(isHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
	if(!isHolding) 
	{
		ACharacter* OurPlayerController = UGameplayStatics::GetPlayerCharacter(this, 0);
		UCameraComponent* PlayerCamera = OurPlayerController->FindComponentByClass<UCameraComponent>();
		FVector ForwardVector = PlayerCamera->GetForwardVector();
		MyMesh->AddForce(ForwardVector*100000*MyMesh->GetMass());
	}
}

