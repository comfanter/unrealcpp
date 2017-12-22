// Harrison McGuire
// UE4 Version 4.18.2
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#include "HideActor.h"

// Called when the game starts or when spawned
void AHideActor::BeginPlay()
{
	Super::BeginPlay();

	if (HideInGame)
	{ 
		DisableActor(HideInGame); 
	}
	
}

// Called every frame
void AHideActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHideActor::DisableActor(bool toHide) 
{
	// Hides visible components
	SetActorHiddenInGame(toHide);

	// Disables collision components
	SetActorEnableCollision(false);

	// Stops the Actor from ticking
	SetActorTickEnabled(false);
}

