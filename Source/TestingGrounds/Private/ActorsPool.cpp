// Copyright dannydev. All Rights Reserved

#include "ActorsPool.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UActorsPool::UActorsPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorsPool::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UActorsPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UActorsPool::Add(AActor* newActor) {
	// Make sure there's something to add
	if (!newActor)
		return;

	// Add to the pool if the item isn't in there already
	if (!pool.Contains(newActor))
		pool.Push(newActor);
}

AActor* UActorsPool::Lend() {
	// Return nullptr when there are no actors in the pool
	if (pool.Num() <= 0)
		return nullptr;

	// Pop the actor from the pool and give it to the caller
	return pool.Pop();
}

void UActorsPool::ReceiveReturn(AActor* returnedActor) {
	// Call the Add function which does the same thing pretty much
	Add(returnedActor);
	
	// Get rid of the returnedActor reference for the caller
	returnedActor = nullptr;
}
