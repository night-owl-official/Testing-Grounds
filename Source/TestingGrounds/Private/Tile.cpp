// Copyright dannydev. All Rights Reserved

#include "Tile.h"
#include "Engine/World.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActor(TSubclassOf<AActor> objectToSpawn,
	const int minAmountToSpawn,
	const int maxAmountToSpawn) {
	// Make sure there is an actor to spawn
	if (objectToSpawn) {
		// Get random number of objects to spawn between min and max amount
		const int32 RANDOM_AMOUNT_TO_SPAWN =
			FMath::RandRange(minAmountToSpawn, maxAmountToSpawn);

		FVector randomPointOnTile;
		FRotator randomObjectRotation;
		// Spawn a random amount of objects
		for (size_t i = 0; i < RANDOM_AMOUNT_TO_SPAWN; i++) {
			// Generate a random point on the tile
			randomPointOnTile = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
			// Generate a random rotation
			randomObjectRotation = FRotator(0.0f, FMath::RandRange(0, 360), 0.0f);
			AActor* spawnedObject = GetWorld()->SpawnActor<AActor>(objectToSpawn,
				randomPointOnTile,
				randomObjectRotation);
			// Attach to its parent tile
			spawnedObject->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}
