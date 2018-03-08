// Copyright dannydev. All Rights Reserved

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	FColor sphereColor;
	sphereColor = CastSphere(GetActorLocation(), 300.0f) ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), GetActorLocation(), 300.0f, 20, sphereColor, false, 10.0f);

	sphereColor = CastSphere(GetActorLocation() + FVector(400.0f, 0.0f, -500.0f), 300.0f) ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), GetActorLocation() + FVector(400.0f, 0.0f, -500.0f), 300.0f, 20, sphereColor, false, 10.0f);
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

bool ATile::CastSphere(const FVector& castLocation, float radius) const {
	// Store what was hit in here
	FHitResult hitResult;
	
	// Cast the sphere of given radius at the given location
	// TRUE if there is any blocking hit entry
	return GetWorld()->SweepSingleByChannel(hitResult,
		castLocation,
		castLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(radius));
}
