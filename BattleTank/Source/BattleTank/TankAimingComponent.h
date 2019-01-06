// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

 // Forward Declaration
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


protected:

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	// Called when the game starts

	void SetBarrelReference(UTankBarrel* barrelToSet);
	void SetTurretReference(UTankTurret* turretToSet);
	virtual void BeginPlay() override;
	void AimAt(FVector hitLocation, float launchSpeed);

private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	void MoveBarrel(FVector aimDirection);
	void MoveTurret(FVector aimDirection);

};
