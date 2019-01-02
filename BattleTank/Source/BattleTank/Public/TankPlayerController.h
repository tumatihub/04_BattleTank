// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float CrosshairXPosition = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYPosition = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& CameraWorldLocation) const;

	FVector GetLookVectorHitLocation(FVector LookDirection, FVector CameraWorldLocation) const;
};
