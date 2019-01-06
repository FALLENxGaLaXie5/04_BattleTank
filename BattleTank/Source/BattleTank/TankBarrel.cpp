// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float relativeSpeed)
{

	// move the barrel the right amount this frame

	//given a max elevation sped, and the frame time

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto elevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + elevationChange;
	auto elevation = FMath::Clamp<float>(rawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(elevation, 0, 0));

}


