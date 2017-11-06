// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#include "MySweepActor.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMySweepActor::AMySweepActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMySweepActor::BeginPlay()
{
	Super::BeginPlay();

	/*TArray is the collection that contains all the HitResults*/
	TArray<FHitResult> HitResults;
	
	/*The Start location of the sphere*/
	FVector StartLocation = GetActorLocation();

	/*The End location of the sphere is equal to the default location of the actor plus the height we will enter from the editor
	To extend this functionality, you can replace the height variable with a FVector*/
	FVector EndLocation = GetActorLocation();
	EndLocation.Z += SphereHeight;

	/*Search for static objects only*/
	ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;

	/*Declare the Collision Shape, assign a Sphere shape and set it's radius*/
	// FCollisionShape CollisionShape;
	// CollisionShape.ShapeType = ECollisionShape::Sphere;
	// CollisionShape.SetSphere(SphereRadius);

	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.0f); // 5M Radius

	// TArray<FHitResults> OutResults;

	// GetWorld()->SweepMultiByChannel(OutResults, SweepStart, SweepEnd, FQuat::Identity, TraceChannel, MySphere);

	/*Perform the actual raycast. This method returns true if there is at least 1 hit.*/
	// bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);
	
	bool bHitSomething = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	/*If the raycast hit a number of objects, iterate through them and print their name in the console*/
	if (bHitSomething)
	{

		for (auto& Hit : HitResults)
		{
			if (GEngine) 
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *Hit.Actor->GetName()));
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("All Hit Information: %s"), *Hit.ToString()));
			}						
		}
	}

	/*In order to draw the sphere of the first image, I will use the DrawDebugSphere function which resides in the DrawDebugHelpers.h
	This function needs the center of the sphere which in this case is provided by the following equation*/
	FVector CenterOfSphere = ((EndLocation - StartLocation) / 2) + StartLocation;

	/*Draw the sphere in the viewport*/
	DrawDebugSphere(GetWorld(), CenterOfSphere, MyColSphere.GetSphereRadius(), Segments, FColor::Green, true);

	DrawDebugPoint(
		GetWorld(), 
		DLocation,
		400,  					//size
		FColor(155,0,155),  
		true  				//persistent (never goes away)
	);

	DrawDebugSphere(
		GetWorld(),
		DLocation, 
		500, 
		32, 
		FColor(255,0,255),
		true
	);
	
}

// Called every frame
void AMySweepActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

