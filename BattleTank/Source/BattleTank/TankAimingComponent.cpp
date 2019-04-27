// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	lastfireTime = FPlatformTime::Seconds();

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (ammoCount <= 0)
	{
		firingState = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - lastfireTime) < reloadTimeInSeconds)
	{
		firingState = EFiringStatus::Reloading;
	}
	else if (isBarrelMoving())
	{
		firingState = EFiringStatus::Aiming;
	}
	else
	{
		firingState = EFiringStatus::Locked;
	}
}


EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return ammoCount;
}


bool UTankAimingComponent::isBarrelMoving()
{
	if (!ensure(barrel)) { return false; }
	auto barrelForward = barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection, 0.01);//vectors are equal
}

void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (!ensure(barrel && turret))	{ return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	//calculate the outLaunchVelocity
	bool iHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace); // parameter must be present to prevent bug
	if (iHaveAimSolution)
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);
		MoveTurret(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	if (!ensure(barrel && turret)) { return; }

	//work-out difference between current barrel rotation, and AimDirection
	auto barrelRotation = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotation;

	barrel->Elevate(deltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector aimDirection)
{
	//work-out difference between current barrel rotation, and AimDirection
	auto turretRotation = turret->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - turretRotation;
	if (FMath::Abs(deltaRotator.Yaw) < 180)
	{
		turret->RotateTurret(deltaRotator.Yaw);
	}
	else
	{
		turret->RotateTurret(-deltaRotator.Yaw);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet) 
{
	barrel = barrelToSet;
	turret = turretToSet;
}


void UTankAimingComponent::Fire()
{
	
	if (firingState == EFiringStatus::Locked || firingState == EFiringStatus::Aiming)
	{
		// spawn a projectile at the socket location of the barrel
		if (!ensure(barrel))	{ return; }
		if (!ensure(projectileBP)) { return; }
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(launchSpeed);
		lastfireTime = FPlatformTime::Seconds();
		ammoCount--;
	}
}