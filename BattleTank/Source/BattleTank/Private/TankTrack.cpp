// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// calculate the slippage speed
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // essentially taking cos of these 2 angles to get "parallelness"
	// work-out the required acceleration this frame to correct
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
	// calculate and apply sideways force
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	auto time = GetWorld()->GetTimeSeconds();
	auto name = GetName();

	//TODO need to clamp these values
	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	UE_LOG(LogTemp, Warning, TEXT("Adding Force!!"));


}