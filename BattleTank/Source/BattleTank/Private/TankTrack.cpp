// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	auto time = GetWorld()->GetTimeSeconds();
	auto name = GetName();

	//TODO need to clamp these values
	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}