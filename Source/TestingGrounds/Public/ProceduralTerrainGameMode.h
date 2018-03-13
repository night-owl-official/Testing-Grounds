// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "ProceduralTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AProceduralTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()

public:
	/** Sets the default properties for this class */
	AProceduralTerrainGameMode();

protected:
	/** Finds all the navmesh volumes in the world and
	 ** passes them to the function that will add them to the pool */
	UFUNCTION(BlueprintCallable, Category = "Actors Pool")
	void PopulateBoundsVolumePool() const;

private:
	/** Adds all the given navmesh bound volumes to the pool */
	void AddToPool(class ANavMeshBoundsVolume* navMeshBoundsVolume) const;

protected:
	/** Pool of NavMeshBoundsVolumes */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Actors Pool")
	class UActorsPool* NavMeshBoundsVolumePool = nullptr;
};
