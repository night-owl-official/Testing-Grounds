// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/** Places an actor in the world at a random viable location */
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActor() const;

private:
	/** Min point where an actor can spawn on the tile */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector MinPoint = FVector(501.0f, -1591.0f, -434.0f);

	/** Max point where an actor can spawn on the tile */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector MaxPoint = FVector(3494.0f, 1391.0f, -434.0f);
	
};
