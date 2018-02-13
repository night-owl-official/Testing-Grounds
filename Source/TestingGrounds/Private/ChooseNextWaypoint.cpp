// Copyright dannydev. All Rights Reserved

#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) {
	// Log for now
	UE_LOG(LogTemp, Warning, TEXT("Executing task"));

	return EBTNodeResult::Succeeded;
}