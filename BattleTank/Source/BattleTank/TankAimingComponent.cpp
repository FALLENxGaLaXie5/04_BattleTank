// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * barrelToSet)
{
	if (!barrelToSet)
	{
		return;
	}
	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * turretToSet)
{
	if (!turretToSet)
	{
		return;
	}
	turret = turretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel || !turret)	{ return; }

	FVector outLaunchVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	//calculate the outLaunchVelocity
	bool iHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace); // parameter must be present to prevent bug
	if (iHaveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);
		MoveTurret(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
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

	turret->RotateTurret(deltaRotator.Yaw);
}

