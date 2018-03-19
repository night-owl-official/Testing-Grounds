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

public:
	/**
	 * Getter for score
	 * @return The score
	 */
	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetScore() const;

	/**
	 * Resets score to zero
	 */
	UFUNCTION(BlueprintCallable, Category = "Score")
	void ResetScore();

	/**
	 * Resets the conquered tile boolean to false
	 */
	UFUNCTION(BlueprintCallable, Category = "Score")
	void ResetWasTileAlreadyConquered();

	/**
     * Increases the score when a tile is conquered
	 */
	UFUNCTION(BlueprintCallable, Category = "Score")
	void TileConquered();


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

private:
	/**
	 * Current score based on how many tiles the user conquered
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Score")
	int32 score = 1;


	/**
	 * Whether the current tile has already been conquered
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Score")
	bool wasTileAlreadyConquered = true;
};
