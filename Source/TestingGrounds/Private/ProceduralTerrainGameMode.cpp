// Copyright dannydev. All Rights Reserved

#include "ProceduralTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ActorsPool.h"

AProceduralTerrainGameMode::AProceduralTerrainGameMode() {
	// Make the pool of NavMeshBoundsVolumes
	NavMeshBoundsVolumePool =
		CreateDefaultSubobject<UActorsPool>(TEXT("NavMeshBoundsVolumePool"));
}

int32 AProceduralTerrainGameMode::GetScore() const {
	return score;
}

void AProceduralTerrainGameMode::ResetScore() {
	score = 0;
}

void AProceduralTerrainGameMode::ResetWasTileAlreadyConquered() {
	wasTileAlreadyConquered = false;
}

void AProceduralTerrainGameMode::TileConquered() {
	// Increase score and set tile conquered to true
	if (!wasTileAlreadyConquered) {
		score++;
		wasTileAlreadyConquered = true;
	}
}

void AProceduralTerrainGameMode::PopulateBoundsVolumePool() const {
	// Array of actors that will store all the navmesh bounds volumes
	// found in the world
	TArray<AActor*> navmeshBoundsVolumes;
	// Get all the actors of type NavigationSystem from the world
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANavMeshBoundsVolume::StaticClass(), navmeshBoundsVolumes);

	// If there is any navmesh bounds volume go through the array
	// and pass every single one to the function that adds them to the pool
	if (navmeshBoundsVolumes.Num() > 0)
		for (AActor* boundsVolume : navmeshBoundsVolumes)
			AddToPool(Cast<ANavMeshBoundsVolume>(boundsVolume));
}

void AProceduralTerrainGameMode::AddToPool(ANavMeshBoundsVolume* navMeshBoundsVolume) const {
	// Make sure there is a navmesh volume
	if (!ensure(navMeshBoundsVolume))
		return;

	// Pass the bounds volume to the pool if there's one
	if (!NavMeshBoundsVolumePool)
		return;

	NavMeshBoundsVolumePool->Add(navMeshBoundsVolume);
}
