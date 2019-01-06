// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// no need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel * barrelToSet)
{
	TankAimingComponent->SetBarrelReference(barrelToSet);
	barrel = barrelToSet;
}

void ATank::SetTurretReference(UTankTurret * turretToSet)
{
	TankAimingComponent->SetTurretReference(turretToSet);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastfireTime) > reloadTimeInSeconds;
	UE_LOG(LogTemp, Warning, TEXT("BOOOOOOM BITCHHHH"));
	if (barrel && isReloaded)
	{
		// spawn a projectile at the socket location of the barrel
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, barrel->GetSocketLocation(FName("Projectile")), barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(launchSpeed);
		lastfireTime = FPlatformTime::Seconds();
	}
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation)
{
	TankAimingComponent->AimAt(hitLocation, launchSpeed);
}