// Harrison McGuire
// UE4 Version 4.18.3
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "OpenDoorTimelineCurve.generated.h"

UCLASS()
class UNREALCPP_API AOpenDoorTimelineCurve : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOpenDoorTimelineCurve();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
 
    /*The timeline that will make the actor float*/
    FTimeline MyTimeline;

    void OpenDoor();

	UPROPERTY(EditAnywhere)
    UCurveFloat* MyCurveFloat;
};
