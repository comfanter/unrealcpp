// UE4 Version 4.18
// Harrison McGuire
// https://github.com/Harrison1
// https://severallevels.io/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConsoleLog.generated.h"

UCLASS()
class UNREALCPP_API AConsoleLog : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConsoleLog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Disable")
	bool HideInGame;
	
};
