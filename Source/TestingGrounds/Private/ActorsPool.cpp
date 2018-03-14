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

	// ...
	
}


// Called every frame
void UActorsPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorsPool::Add(AActor* newActor) {
	// Make sure there's something to add
	if (!newActor)
		return;

	// Temp log
	UE_LOG(LogTemp, Warning, TEXT("%s added to the pool"), *(newActor->GetName()));
}

AActor* UActorsPool::Lend() {

	// Temp log
	UE_LOG(LogTemp, Warning, TEXT("Actor lend"));

	return nullptr;
}

void UActorsPool::ReceiveReturn(AActor* returnedActor) {
	// Make sure there's something to add
	if (!returnedActor)
		return;

	// Temp log
	UE_LOG(LogTemp, Warning, TEXT("%s returned to the pool"), *(returnedActor->GetName()));
}
