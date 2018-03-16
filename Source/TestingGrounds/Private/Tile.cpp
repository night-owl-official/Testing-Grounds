// Copyright dannydev. All Rights Reserved

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorsPool.h"
#include "AI/Navigation/NavigationSystem.h"

// Sets default values
ATile::ATile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay() {

	Super::BeginPlay();
}

// Called when the game ends or when about to get destroyed
void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason) {

	Super::EndPlay(EndPlayReason);

	// Return the borrowed actor to the pool if possible
	if (actorsPool && borrowedActor)
		actorsPool->ReceiveReturn(borrowedActor);
}

// Called every frame
void ATile::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
}

void ATile::SetActorsPool(UActorsPool* poolOfActors) {
	// Make sure the argument isn't null
	if (!poolOfActors)
		return;

	// Set it
	actorsPool = poolOfActors;

	BorrowActorFromPoolAndSetItsLocation();
}

void ATile::PlaceActors(TSubclassOf<AActor> objectToSpawn,
	const int minAmountToSpawn,
	const int maxAmountToSpawn,
	float spawnRadiusRange) {
	// Make sure there is an actor to spawn
	if (objectToSpawn) {
		// Get the array of FSpawnPositions
		TArray<FSpawnPosition> spawnPositions =
			GenerateSpawnPositions(minAmountToSpawn, maxAmountToSpawn, spawnRadiusRange);

		// Loop through the FSpawnPositions until all the actors are placed
		for (const FSpawnPosition& spawnPos : spawnPositions)
			// Place it on the tile
			PlaceActor(objectToSpawn, spawnPos);
	}
}

TArray<FSpawnPosition> ATile::GenerateSpawnPositions(const int32 minSpawns,
	const int32 maxSpawns,
	const float radiusRange) const {
	// FSpawnPosition array to return
	TArray<FSpawnPosition> spawnPositions;

	// Get random number of objects to spawn between min and max amount
	const size_t RANDOM_AMOUNT_TO_SPAWN =
		FMath::RandRange(minSpawns, maxSpawns);

	FSpawnPosition spawnPositionToAdd;
	// Spawn a random amount of objects
	for (size_t i = 0; i < RANDOM_AMOUNT_TO_SPAWN; i++) {
		// Generate a random scale
		spawnPositionToAdd.scale = FMath::RandRange(MinScale, MaxScale);
		// Generate a random rotation
		spawnPositionToAdd.rotation = FRotator(0.0f,
			FMath::RandRange(minSpawnedObjectRotationDeg,
				maxSpawnedObjectRotationDeg),
			0.0f);

		// Place an actor only if there was an empty location
		if (FindEmptyLocation(spawnPositionToAdd.location, radiusRange * spawnPositionToAdd.scale))
			// Add it to the array
			spawnPositions.Add(spawnPositionToAdd);
	}

	return spawnPositions;
}

bool ATile::IsPossibleToSpawnObject(const FVector& castLocation, float radius) const {
	// Store what was hit in here
	FHitResult hitResult;
	
	// Convert the location of the cast from local to world
	// because that's how it's treated in function below
	FVector globalCastLocation = ActorToWorld().TransformPosition(castLocation);

	// Cast the sphere of given radius at the given location
	bool hasHitAnything = GetWorld()->SweepSingleByChannel(hitResult,
		globalCastLocation,
		globalCastLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(radius));

	//// Draw a debug sphere for visualization
	//FColor sphereColor = hasHitAnything ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), globalCastLocation, 0.0f, radius, FQuat::Identity, sphereColor, false, 60.0f);

	// TRUE if there isn't any blocking hit entry
	return !hasHitAnything;
}

void ATile::PlaceActor(TSubclassOf<AActor> toSpawn, const FSpawnPosition& spawnPosition) {
	// Spawn the actor
	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(toSpawn,
		spawnPosition.location,
		spawnPosition.rotation);
	// Set object scale
	spawnedActor->SetActorScale3D(FVector(spawnPosition.scale));
	// Attach to its parent tile
	spawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

bool ATile::FindEmptyLocation(FVector& outSpawnPoint, float spawnRadius) const {
	// Max number of possible loops
	const int MAX_AMOUNT_OF_LOOPS = 100;
	// Counter used to choose how many times this should loop
	int counter = 0;

	do {
		// Generate a random point on the tile
		outSpawnPoint = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));

		// Increase counter if the spot wasn't empty
		// TRUE if the location was empty
		if (IsPossibleToSpawnObject(outSpawnPoint, spawnRadius))
			return true;
		else
			counter++;
	} while (counter < MAX_AMOUNT_OF_LOOPS);

	return false;
}

void ATile::BorrowActorFromPoolAndSetItsLocation() {
	// Make sure there is a pool
	if (!actorsPool)
		return;

	// Borrow the actor
	borrowedActor = actorsPool->Lend();

	// Move its location if it was successfully borrowed
	if (borrowedActor)
		borrowedActor->SetActorLocation(GetActorLocation() + navMeshOffset);

	// Build the navigation system
	GetWorld()->GetNavigationSystem()->Build();
}
