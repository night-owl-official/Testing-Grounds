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
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Patrolling")
		TArray<AActor*> _patrollingPoints;	// Points this unit can go to and patrol
};
