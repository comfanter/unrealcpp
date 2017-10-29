// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io/

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))
#include "MyTriggerBox.h"

void AMyTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnTriggerEnter);
    OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnTriggerExit);

}

void AMyTriggerBox::OnTriggerEnter(AActor* Box, AActor* OverlappingActor)
{
    // print to screen using above defined method when actor enters trigger box
    printFString("Overlapped Actor = %s", *OverlappingActor->GetName());    
}

void AMyTriggerBox::OnTriggerExit(AActor* Box, AActor* OverlappingActor)
{
    // print to screen using above defined method when actor leaves trigger box
    print("Overlap Ended");
}