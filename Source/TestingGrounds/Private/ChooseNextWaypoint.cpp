// Copyright dannydev. All Rights Reserved

#include "ChooseNextWaypoint.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) {
	// Get the blackboard
	auto blackboardComponent = OwnerComp.GetBlackboardComponent();
	// Get the waypoint index from the patrol blackboard
	auto waypointIndex = blackboardComponent->GetValueAsInt(WaypointIndex.SelectedKeyName);

	// Log for now
	UE_LOG(LogTemp, Warning, TEXT("Next waypoint index: %d"), waypointIndex);

	return EBTNodeResult::Succeeded;
}