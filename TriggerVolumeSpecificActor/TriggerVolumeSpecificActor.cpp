// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io/

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))

#include "TriggerVolumeSpecificActor.h"

ATriggerVolumeSpecificActor::ATriggerVolumeSpecificActor()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &ATriggerVolumeSpecificActor::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ATriggerVolumeSpecificActor::OnOverlapEnd);
}

void ATriggerVolumeSpecificActor::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    //if the overlapping actor is the specific actor we identified in the editor
    if (OtherActor && (OtherActor != this) && OtherActor == SpecificActor )
    {
        print("Overlap Begin");
        printFString("Overlapping Actor = %s", *OtherActor->GetName());
    }
}

void ATriggerVolumeSpecificActor::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
    //if the overlapping actor is the specific actor we identified in the editor
    if (OtherActor && (OtherActor != this) && OtherActor == SpecificActor )
    {
        print("Overlap End");
        printFString("%s has left the Trigger Box", *OtherActor->GetName());
    }
}


