// UE4 Version 4.18
// Harrison McGuire
// https://github.com/Harrison1
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

	// overide BeginPlay()
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerEnter(AActor* Box, AActor* OverlappingActor);

	UFUNCTION()
	void OnTriggerExit(AActor* Box, AActor* OverlappingActor);
	
};
