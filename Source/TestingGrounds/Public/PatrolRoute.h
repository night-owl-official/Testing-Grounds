// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"

/**
* Helps AI choose which path to follow next
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrolRoute();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/*
	* Getter for patrolling points
	*/
	UFUNCTION(BlueprintCallable, Category = "Patrol Route")
		TArray<AActor*> GetPatrollingPoints() const;

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray<AActor*> _patrollingPoints;	// Points this unit can go to and patrol
};
