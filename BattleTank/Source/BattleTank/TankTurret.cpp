// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::RotateTurret(float relativeSpeed)
{
	// move the barrel the right amount this frame

	//given a max elevation sped, and the frame time

	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto rotationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewRotation = RelativeRotation.Yaw + rotationChange;
	//auto newRotation = FMath::Clamp<float>(rawNewRotation, MinRotation, MaxRotation);

	SetRelativeRotation(FRotator(0, rawNewRotation, 0));
}


