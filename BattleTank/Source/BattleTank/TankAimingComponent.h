// Copyright Josh Inc.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankAimingComponent.generated.h"

//enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

 // Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;



// Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingState = EFiringStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int32 ammoCount = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> projectileBP;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float launchSpeed = 100000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeInSeconds = 3;
public:	

	// Called when the game starts
	virtual void BeginPlay() override;
	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);


	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();
	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetRoundsLeft() const;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	

	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	FVector aimDirection;

	void MoveBarrel(FVector aimDirection);
	void MoveTurret(FVector aimDirection);
	bool isBarrelMoving();


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	

	double lastfireTime = 0;
};