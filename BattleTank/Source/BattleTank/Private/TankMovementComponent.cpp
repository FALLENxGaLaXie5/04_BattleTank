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
	
	auto tankName = GetOwner()->GetName();
	auto moveVelocityString = MoveVelocity.ToString();

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *tankName, *moveVelocityString);

	
	auto tankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntentionVector = MoveVelocity.GetSafeNormal();
	auto forwardThrow = FVector::DotProduct(tankForwardVector, AIForwardIntentionVector);
	auto rightThrow = FVector::CrossProduct(tankForwardVector, AIForwardIntentionVector).Z;
	IntendMoveForward(forwardThrow);
	IntendTurnRight(rightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), rightThrow, forwardThrow);

	//UE_LOG(LogTemp, Warning, TEXT("%s Move Velocity: %s"), *tankName, *AIForwardIntention);

}


void  UTankMovementComponent::IntendMoveForward(float throwIt)
{
	if (!ensure(leftTrack && rightTrack))
	{
		return;
	}
	leftTrack->SetThrottle(throwIt);
	rightTrack->SetThrottle(throwIt);
	//TODO prevent double-speed due to dual control use
}

void  UTankMovementComponent::IntendTurnRight(float throwIt)
{
	if (!ensure(leftTrack && rightTrack))
	{
		return;
	}
	leftTrack->SetThrottle(throwIt);
	rightTrack->SetThrottle(-throwIt);
	//TODO prevent double-speed due to dual control use
}
