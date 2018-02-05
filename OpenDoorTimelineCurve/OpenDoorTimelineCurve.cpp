// Harrison McGuire
// UE4 Version 4.18.3
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

// helpful links
// https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/Components/FTimeline/

#include "OpenDoorTimelineCurve.h"


// Sets default values
AOpenDoorTimelineCurve::AOpenDoorTimelineCurve()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}
