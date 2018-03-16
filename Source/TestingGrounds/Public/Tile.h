// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

/**
 * FSpawnPosition is a struct used
 * to have a compact form of location, rotation and scale
 * for a newly spawned object on the tile
 */
USTRUCT()
struct FSpawnPosition {
	GENERATED_USTRUCT_BODY()

public:
	FVector location;
	FRotator rotation;
	float scale;
};


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

	// Called when the game ends or when about to be destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** Sets the reference to the pool of actors */
	UFUNCTION(BlueprintCallable, Category = "Actors Pool")
	void SetActorsPool(class UActorsPool* poolOfActors);

protected:
	/** Places actors in the world at a random viable location */
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActors(TSubclassOf<AActor> objectToSpawn,
		const int32 minAmountToSpawn,
		const int32 maxAmountToSpawn,
		float spawnRadiusRange);

	/** Places AI pawns in the world at a random viable location */
	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceAIPawns(TSubclassOf<APawn> pawnToSpawn,
		const int32 minAmountToSpawn,
		const int32 maxAmountToSpawn,
		float spawnRadiusRange);

private:
	/** Places actors in the world at a random viable location */
	template <class T>
	void RandomlyPlaceActors(TSubclassOf<T> actorToSpawn,
		const int32 minAmountToSpawn,
		const int32 maxAmountToSpawn,
		float spawnRadiusRange);

	/** Spawns an actor at the given location */
	void PlaceActor(TSubclassOf<AActor> toSpawn, const FSpawnPosition& spawnPosition);

	/** Spawns a pawn at the given location */
	void PlaceActor(TSubclassOf<APawn> toSpawn, const FSpawnPosition& spawnPosition);

	/** Tries to find an empty location for an object to spawn */
	bool FindEmptyLocation(FVector& outSpawnPoint, float spawnRadius) const;

	/** Casts a sphere at the spawned actor location, used to check
	 ** if there's anything around it */
	bool IsPossibleToSpawnObject(const FVector& castLocation, float radius) const;

	/** Borrows an actor (likely will be a bounds volume) from the pool
	 ** and moves it to the current tile's location */
	void BorrowActorFromPoolAndSetItsLocation();

private:
	/** Min point where an actor can spawn on the tile */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector MinPoint = FVector(148.0f, -1979.0f, -484.0f);

	/** Max point where an actor can spawn on the tile */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector MaxPoint = FVector(3878.0f, 1757.0f, -484.0f);

	/**
	* Min rotation in degrees for a spawned object on the tile
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float minSpawnedObjectRotationDeg = -180.0f;

	/**
	* Max rotation in degrees for a spawned object on the tile
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float maxSpawnedObjectRotationDeg = 180.0f;

	/** Min scale a spawned object can have */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float MinScale = 1.0f;

	/** Max scale a spawned object can have */
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float MaxScale = 1.0f;

	/** Pool of actors to access */
	UPROPERTY(VisibleDefaultsOnly, Category = "Actors Pool")
	class UActorsPool* actorsPool = nullptr;

	/** Offset used to position the navmesh on the next tile */
	UPROPERTY(EditDefaultsOnly, Category = "Actors Pool")
	FVector navMeshOffset = FVector(2000.0f, 0.0f, -350.0f);
	
	/** Actor that is borrowed from the pool */
	AActor* borrowedActor = nullptr;
};
