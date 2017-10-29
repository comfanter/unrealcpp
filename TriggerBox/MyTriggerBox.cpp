// UE4 Version 4.18
// Harrison McGuire
// https://github.com/Harrison1
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
    printFString("Overlapped Actor = %s", *OverlappingActor->GetName());    
}

void AMyTriggerBox::OnTriggerExit(AActor* Box, AActor* OverlappingActor)
{
    print("Overlap Ended");
}