// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingUnit.generated.h"

/**
 * Allows classes who inherits from this one, to have points to patrol
 */
UCLASS()
class TESTINGGROUNDS_API APatrollingUnit : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()

public:
	/*
	* Getter for patrolling points
	*/
	UFUNCTION(BlueprintCallable, Category = "Patrolling")
		TArray<AActor*> GetPatrollingPoints() const;
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Patrolling")
		TArray<AActor*> _patrollingPoints;	// Points this unit can go to and patrol

	// TODO Add other target point to the guards' initial location
};
