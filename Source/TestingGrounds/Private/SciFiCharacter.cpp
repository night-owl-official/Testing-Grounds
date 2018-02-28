// Copyright dannydev. All Rights Reserved

#include "SciFiCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Gun.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
ASciFiCharacter::ASciFiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FP_Camera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -157.0f);
}

// Called when the game starts or when spawned
void ASciFiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Spawn gun blueprint
	if (!ensure(GunBlueprint))
		return;

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	//Attach gun blueprint component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	// Attach to FP if it's player controlled, TP if it's AI controlled
	if (IsPlayerControlled())
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	else
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Set gun's animation instance
	Gun->FPAnimationInstance = Mesh1P->GetAnimInstance();
	Gun->TPAnimationInstance = GetMesh()->GetAnimInstance();

	// Bind fire input
	if (InputComponent)
		InputComponent->BindAction("Fire", IE_Pressed, this, &ASciFiCharacter::PullTrigger);
}

// Called every frame
void ASciFiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASciFiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASciFiCharacter::UnPossessed() {
	Super::UnPossessed();

	// Attach gun to the TP mesh when player dies
	if (Gun)
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void ASciFiCharacter::PullTrigger() {
	if (!ensure(Gun))
		return;

	Gun->OnFire();
	// Report noise event if you're the player
	AActor* controlledActor = Cast<AActor>(GetController()->GetPawn());
	if (controlledActor)
		if (controlledActor->ActorHasTag(TEXT("Player")))
			UAISense_Hearing::ReportNoiseEvent(this, controlledActor->GetActorLocation(), 1.0f, controlledActor);
}
