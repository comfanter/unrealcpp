// Harrison McGuire 
// UE4 Version 4.18.2 
// https://github.com/Harrison1/unrealcpp 
// https://severallevels.io 
// https://harrisonmcguire.com
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/FTimerManager/SetTimer/4/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/AActor/SetActorRelativeRotation/2/index.html
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/USceneComponent/GetComponentRotation/index.html
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Kismet/UKismetSystemLibrary/DrawDebugBox/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/DrawDebugBox/2/
// https://docs.unrealengine.com/latest/INT/API/Runtime/Core/Math/FVector/DotProduct/index.html
// WIP

#include "SwingDoor.h"
// add constructor header
#include "ConstructorHelpers.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

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

	CalcThree = 0.0f;
	degree = 0.0f;
	AddRot = 0.0f;

}

// Called when the game starts or when spawned
void ASwingDoor::BeginPlay()
{
	Super::BeginPlay();

	// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("actor location: %s"), *GetActorLocation().ToString()));

	DrawDebugBox(GetWorld(), GetActorLocation(), BoxComp->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::Turquoise, true, -1, 0, 2);
	
}

// Called every frame
void ASwingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	float CurrentRotation = Door->RelativeRotation.Yaw;

	// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("rotation max: %f"), CurrentRotation));

	if(CalcThree > 0) {
		degree = 90.0f;
		AddRot = dt*50;
	} else {
		degree = -90.0f;
		AddRot = -dt*50;
	}

	if(Opening && !FMath::IsNearlyEqual(CurrentRotation, degree, 0.5f))
	{
		// CurrentRotation += dt*50;
		// float AddRot = dt*50;
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

	float CurrentRotation = Door->RelativeRotation.Yaw;

	if(CurrentRotation > 0) {
		MinusRot = -dt*50;
	} else {
		MinusRot = +dt*50;
	}

	if(Closing && !FMath::IsNearlyEqual(CurrentRotation, 0.0f, 0.5f))
	{
		// CurrentRotation -= dt*50;
		// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("rotation: %f"), CurrentRotation));
		// CurrentRotation = FMath::Clamp(CurrentRotation, 0.0f, 90.0f);
		// float MinusRot = -dt*50;
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

	// UE_LOG(LogTemp,Warning,TEXT("Door FV: %s"), *Door->GetForwardVector().ToString());
	// UE_LOG(LogTemp,Warning,TEXT("Box Comp: %s"), *BoxComp->GetForwardVector().ToString());

	//Find the actor that handles control for the local player.
	// ACharacter* OurPlayerController = UGameplayStatics::GetPlayerCharacter(this, 0);

	// UCameraComponent* PlayerCamera = OurPlayerController->FindComponentByClass<UCameraComponent>();

	// FVector ForwardVector = PlayerCamera->GetForwardVector();

	// UE_LOG(LogTemp,Warning,TEXT("Camera FV FROM THE DOOR ACTOR: %s"), *ForwardVector.ToString());

	// float Calc = Door->GetForwardVector().X + ForwardVector.X;
	// float CalcTwo = FVector::DotProduct(Door->GetForwardVector(), ForwardVector);

	// // Good Take Calc Three
	// float CalcThree = FVector::DotProduct(BoxComp->GetForwardVector(), ForwardVector);

	// UE_LOG(LogTemp,Warning,TEXT("Calc: %f"), Calc );
	// UE_LOG(LogTemp,Warning,TEXT("DotProduct: %f"), CalcTwo );
	// UE_LOG(LogTemp,Warning,TEXT("Door FV: %s"), *Door->GetForwardVector().ToString());
	// UE_LOG(LogTemp,Warning,TEXT("DotProduct Three: %f"), CalcThree);

	ACharacter* OurPlayerController = UGameplayStatics::GetPlayerCharacter(this, 0);

	UCameraComponent* PlayerCamera = OurPlayerController->FindComponentByClass<UCameraComponent>();

	FVector ForwardVector = PlayerCamera->GetForwardVector();

	CalcThree = FVector::DotProduct(BoxComp->GetForwardVector(), ForwardVector);

	
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