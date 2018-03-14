// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorsPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UActorsPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorsPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Adds the given actor to the pool */
	void Add(AActor* newActor);

	/** Lends one of its actors from the pool to whoever asks for it */
	AActor* Lend();

	/** Takes back the actor that gets returned from whoever was using it */
	void ReceiveReturn(AActor* returnedActor);
};
