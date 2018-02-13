// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * Takes care of choosing where to move next, among AI target points
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	
private:
	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(Editanywhere, Category = "Blackboard")
		struct FBlackboardKeySelector WaypointIndex;	// Blackboard key selector used to choose a blackboard key from blueprint

	UPROPERTY(Editanywhere, Category = "Blackboard")
		struct FBlackboardKeySelector NextWaypoint;		// Blackboard key selector used to choose a blackboard key from blueprint
};
