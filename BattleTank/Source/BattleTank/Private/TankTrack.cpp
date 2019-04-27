// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit!"))
	ApplySidewaysCorrection();
	DriveTrack();
	currentThrottle = 0;
}

void UTankTrack::ApplySidewaysCorrection()
{
	// calculate the slippage speed
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // essentially taking cos of these 2 angles to get "parallelness"
																						// work-out the required acceleration this frame to correct

	auto deltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();
	// calculate and apply sideways force
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto time = GetWorld()->GetTimeSeconds();
	auto name = GetName();

	//TODO need to clamp these values
	auto forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
	UE_LOG(LogTemp, Warning, TEXT("Adding Force!!"));
}