// Copyright dannydev. All Rights Reserved

#include "ChooseNextWaypoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"

#include "PatrollingUnit.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) {
	// Get the blackboard
	auto blackboardComponent = OwnerComp.GetBlackboardComponent();
	// Make sure there is a blackboard component
	if (!ensure(blackboardComponent))
		return EBTNodeResult::Failed;

	// Get the waypoint index from the patrol blackboard
	int32 waypointIndex = blackboardComponent->GetValueAsInt(WaypointIndex.SelectedKeyName);
	// Get the next waypoint from the patrol blackboard
	// and cast to an actor
	AActor* nextWaypoint =
		Cast<AActor>(blackboardComponent->GetValueAsObject(NextWaypoint.SelectedKeyName));

	// Get controlled pawn from AI controller and cast it to a patrolling unit
	auto AIPatrollingUnit = Cast<APatrollingUnit>(OwnerComp.GetAIOwner()->GetPawn());
	// Get out if there's no pawn
	if (!ensure(AIPatrollingUnit))
		return EBTNodeResult::Failed;

	// Get patrol points
	auto patrolPoints = AIPatrollingUnit->GetPatrollingPoints();
	// Make sure array isn't empty
	if (patrolPoints.Num() > 0) {
		// Set next waypoint based on given index
		blackboardComponent->SetValueAsObject(NextWaypoint.SelectedKeyName, patrolPoints[waypointIndex]);
		// Get the next integer value for the next waypoint
		int32 nextWaypointIndex = ++waypointIndex % patrolPoints.Num();
		// Set next waypoint index on the blackboard
		blackboardComponent->SetValueAsInt(WaypointIndex.SelectedKeyName, nextWaypointIndex);
	}

	return EBTNodeResult::Succeeded;
}