// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io/

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "MyTriggerBox.h"

AMyTriggerBox::AMyTriggerBox()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
}

void AMyTriggerBox::OnOverlapBegin(AActor* Box, AActor* OverlappingActor)
{
    // print to screen using above defined method when actor enters trigger box
    printFString("Overlapped Actor = %s", *OverlappingActor->GetName());    
}

void AMyTriggerBox::OnOverlapEnd(AActor* Box, AActor* OverlappingActor)
{
    // print to screen using above defined method when actor leaves trigger box
    print("Overlap Ended");
}