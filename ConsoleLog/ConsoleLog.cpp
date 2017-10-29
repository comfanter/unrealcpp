// UE4 Version 4.18
// Harrison McGuire
// https://github.com/Harrison1
// https://severallevels.io/

// define a print message function to print to screen
#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
#include "ConsoleLog.h"

// Sets default values
AConsoleLog::AConsoleLog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConsoleLog::BeginPlay()
{
	Super::BeginPlay();

	// Standard way to log to console.
	UE_LOG(LogTemp, Warning, TEXT("I just started running"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
	print("Hello Unreal");	
	
}

// Called every frame
void AConsoleLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Print 'Hello Unreal' on to the screen on every frame
	// print("Hello Unreal");
}

