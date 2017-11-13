// Harrison McGuire
// UE4 Version 4.18
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io

#include "AddRadialForce.h"
// add debug helpfers
#include "DrawDebugHelpers.h"

// Sets default values
AAddRadialForce::AAddRadialForce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAddRadialForce::BeginPlay()
{
	Super::BeginPlay();

	// create tarray for hit results
	TArray<FHitResult> OutHits;

	// crate tarray for sweep actors
	TArray<AActor*> SweepActors;

	// get actor locations
	FVector MyLocation = GetActorLocation();
	
	// start and end locations. The sphere will create the radial sweep.
	FVector SweepStart = MyLocation;
	FVector SweepEnd = MyLocation;

	// create a collision sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.0f);

	// draw collision sphere
	DrawDebugSphere(GetWorld(), GetActorLocation(), MyColSphere.GetSphereRadius(), 50, FColor::Cyan, true);
	
	// check if something got hit in the sweep
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	if (isHit)
	{
		// loop through TArray
		for (auto& Hit : OutHits)
		{
			SweepActors.Add(Hit.GetActor());				
		}
	}

	// loop through sweep actors
	for (auto& SweepActor : SweepActors)
	{
		// you need the prmitive comp to apply radial force. Popular prim comps are CapsuleComponent, StaticMeshComponent, and SkeletalMeshComponent.
		UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((SweepActor)->GetRootComponent());
	
		
		if (MeshComp)
		{
			// alternivly you can use  ERadialImpulseFalloff::RIF_Linear for the impulse to get linearly weaker as it gets further from origin.
			// set the float radius to 500 and the float strength to 2000.
			MeshComp->AddRadialImpulse(GetActorLocation(), 500.f, 2000.f, ERadialImpulseFalloff::RIF_Constant, true);
		}

	}
	
}

// Called every frame
void AAddRadialForce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

