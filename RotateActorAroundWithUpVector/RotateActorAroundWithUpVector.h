// Harrison McGuire UE4 Version 4.18 https://github.com/Harrison1/unrealcpp https://severallevels.io

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateActorAroundWithUpVector.generated.h"

UCLASS()
class UNREALCPP_API ARotateActorAroundWithUpVector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotateActorAroundWithUpVector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// declare our float variables
	UPROPERTY(EditAnywhere, Category = Movement)
	float AngleAxis;

	UPROPERTY(EditAnywhere, Category = Movement)
	float XValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float YValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float ZValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float FXValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float FYValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float FZValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float PlusBy;
	
};
