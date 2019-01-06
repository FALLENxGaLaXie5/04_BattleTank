// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declarations
class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:
	void AimTowardsCrosshair();
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	bool GetSightRayHitLocation(FVector& hitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitlocation) const;
	UPROPERTY(EditAnywhere)
		float lineTraceRange = 1000000.f;
	UPROPERTY(EditAnywhere)
		float crosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float crosshairYLocation = 0.33333f;

};
