// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io/

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "LightSwitchPushButton.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitchPushButton::ALightSwitchPushButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightIntensity = 3000.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->Intensity = LightIntensity;
	PointLight->bVisible = true;
	RootComponent = PointLight;

	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	LightSphere->InitSphereRadius(250.0f);
	LightSphere->SetCollisionProfileName(TEXT("Trigger"));
	LightSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	LightSphere->SetupAttachment(RootComponent);

	LightSphere->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchPushButton::OnOverlapBegin);
	LightSphere->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchPushButton::OnOverlapEnd);

	OurPlayer = NULL;

	isOverlapping = false;

}

// Called when the game starts or when spawned
void ALightSwitchPushButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightSwitchPushButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isOverlapping && OurPlayer->isAction) 
	{
		ToggleLight();
	}

}

void ALightSwitchPushButton::ToggleLight()
{
    PointLight->ToggleVisibility();
}

void ALightSwitchPushButton::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
		print("I am from the the light");
		
		if(OtherActor->GetClass()->IsChildOf(AUnrealCPPCharacter::StaticClass())) {
			printFString("other actor = %s", *OtherActor->GetName());

			isOverlapping = true;

			OurPlayer = Cast<AUnrealCPPCharacter>(OtherActor);

			// if(OurPlayer->isAction) {
			// 	print("action is true");
			// 	ToggleLight();
			// } else {
			// 	print("action is false");
			// }
		}
    }
}

void ALightSwitchPushButton::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
		print("end overlap");
		isOverlapping = false;
        OurPlayer = NULL;
    }
}