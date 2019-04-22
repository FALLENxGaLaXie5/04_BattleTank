// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitializeProperties(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// no need to call super as we're replacing the functionality
	auto tankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntentionVector = MoveVelocity.GetSafeNormal();
	auto dotProduct = FVector::DotProduct(tankForwardVector, AIForwardIntentionVector);
	auto crossProduct = FVector::CrossProduct(tankForwardVector, AIForwardIntentionVector);
	IntendMoveForward(dotProduct);
	IntendTurnRight(crossProduct.Z);
	//UE_LOG(LogTemp, Warning, TEXT("%s Move Velocity: %s"), *tankName, *AIForwardIntention);
}


void  UTankMovementComponent::IntendMoveForward(float throwIt)
{
	if (!leftTrack || !rightTrack)
	{
		return;
	}
	leftTrack->SetThrottle(throwIt);
	rightTrack->SetThrottle(throwIt);
	//TODO prevent double-speed due to dual control use
}

void  UTankMovementComponent::IntendTurnRight(float throwIt)
{
	if (!leftTrack || !rightTrack)
	{
		return;
	}
	leftTrack->SetThrottle(throwIt);
	rightTrack->SetThrottle(-throwIt);
	//TODO prevent double-speed due to dual control use
}
