// Harrison McGuire 
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp 
// https://severallevels.io/

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "TriggerBoxSpecificActor.h"

ATriggerBoxSpecificActor::ATriggerBoxSpecificActor()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxSpecificActor::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ATriggerBoxSpecificActor::OnOverlapEnd);
}

void ATriggerBoxSpecificActor::OnOverlapBegin(class AActor* Box, class AActor* OverlappingActor)
{
    //if the overlapping actor is the specific actor we identified in the editor
    if(OverlappingActor == SpecificActor)
    {
        printFString("Overlapping Actor = %s", *OverlappingActor->GetName());
    }
}

void ATriggerBoxSpecificActor::OnOverlapEnd(class AActor* Box, class AActor* OverlappingActor)
{
    //if the overlapping actor is the specific actor we identified in the editor
    if(OverlappingActor == SpecificActor)
    {
        printFString("%s has left the Trigger Box", *OverlappingActor->GetName());
    }
}