// Copyright dannydev. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

/**
* Responsible for handling actions like firing, reloading etc.
*/
UCLASS()
class TESTINGGROUNDS_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Fire")
	void OnFire();

	/** Sets the animation instance for the 1st person character */
	void SetFPAnimInstance(class UAnimInstance* AnimInstance);

	/** Sets the animation instance for the 1st person character */
	void SetTPAnimInstance(class UAnimInstance* AnimInstance);

public:
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound = nullptr;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FPFireMontage = nullptr;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* TPFireMontage = nullptr;

	/** AnimSequence to play when we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimSequence* RifleFireAnim = nullptr;

	/** AnimInstance to to use for FP fire animation */
	class UAnimInstance* FPAnimationInstance = nullptr;

	/** AnimInstance to to use for TP fire animation */
	class UAnimInstance* TPAnimationInstance = nullptr;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

private:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASciFiRifleProjectile> ProjectileClass = nullptr;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzleLocation = nullptr;

	/** Gun mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Gun = nullptr;
};
