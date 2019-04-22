// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledTank = Cast<ATank>(GetPawn());
	if (playerTank)
	{
		// TODO move towards the player
		MoveToActor(playerTank, acceptanceRadius);//TODO check radius is in cm
		// Aim towards the player

		// Fire if ready
		controlledTank->AimAt(playerTank->GetActorLocation());

		// fire if ready
		controlledTank->Fire(); //TODO don't fire every frame
	}

}