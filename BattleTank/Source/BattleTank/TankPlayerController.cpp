// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector hitLocation = FVector(0); //out parameter
	if (GetSightRayHitLocation(hitLocation))
	{

		GetControlledTank()->AimAt(hitLocation);
		//get world location if linetrace through crosshair
		// if it hits the landscape
			// tell controlled tank to aim at this point
	}
}

// get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	// find the crosshair position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(viewportSizeX * crosshairXLocation, viewportSizeY * crosshairYLocation);

	// "DeProject" the screen position of the crosshair to a world direction
	FVector lookDirection;

	if (GetLookDirection(screenLocation, lookDirection))
	{
		// line-trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(lookDirection, hitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;

	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	FVector playerViewPointLocation = PlayerCameraManager->GetCameraLocation();
	FVector lineTraceEnd = playerViewPointLocation + (lookDirection * lineTraceRange);

	FHitResult hitResult;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, playerViewPointLocation, lineTraceEnd, ECollisionChannel::ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0);
	return false;
}