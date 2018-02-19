// Copyright dannydev. All Rights Reserved

#include "Gun.h"

#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "TestingGroundsProjectile.h"


// Sets default values
AGun::AGun() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a gun mesh component
	Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Gun->bCastDynamicShadow = false;
	Gun->CastShadow = false;
	SetRootComponent(Gun);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(Gun);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void AGun::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AGun::OnFire() {
	// try and fire a projectile
	if (ProjectileClass != NULL) {
			UWorld* const World = GetWorld();
			if (World != NULL) {
				const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<ATestingGroundsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
	}

		// try and play the sound if specified
		if (FireSound != NULL)
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		// try and play a firing animation if specified
		if ((FireAnimation != NULL) && (AnimationInstance != NULL))
			AnimationInstance->Montage_Play(FireAnimation, 1.f);
}