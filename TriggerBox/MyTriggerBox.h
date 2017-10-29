// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io/

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"

UCLASS()
class UNREALCPP_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:

	// constructor sets default values for this actor's properties
	AMyTriggerBox();

	// overlap begin function
	UFUNCTION()
	void OnOverlapBegin(AActor* Box, AActor* OverlappingActor);

	// overlap end function
	UFUNCTION()
	void OnOverlapEnd(AActor* Box, AActor* OverlappingActor);
	
};