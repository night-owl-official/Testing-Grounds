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
	/** Places actors in the world at a random viable location */
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActors(TSubclassOf<AActor> objectToSpawn,
		const int32 minAmountToSpawn,
		const int32 maxAmountToSpawn,
		float spawnRadiusRange);

private:
	/** Casts a sphere at the spawned actor location, used to check
	*** if there's anything around it */
	bool IsPossibleToSpawnObject(const FVector& castLocation, float radius) const;

	/** Spawns an actor at the given location */
	void PlaceActor(TSubclassOf<AActor> toSpawn, const FVector& spawnLocation, float randomScale);

	/** Tries to find an empty location for an object to spawn */
	bool FindEmptyLocation(FVector& outSpawnPoint, float spawnRadius) const;

private:
	/** Min point where an actor can spawn on the tile */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector MinPoint = FVector(501.0f, -1591.0f, -484.0f);

	/** Max point where an actor can spawn on the tile */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector MaxPoint = FVector(3494.0f, 1391.0f, -484.0f);

	/** Min scale a spawned object can have */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float MinScale = 1.0f;

	/** Max scale a spawned object can have */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float MaxScale = 1.0f;
	
};
