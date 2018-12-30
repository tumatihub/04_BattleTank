// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Public/TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; };

	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *OutHitLocation.ToString())
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector LookDirection, CameraWorldLocation, HitLocation;

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXPosition, ViewportSizeY * CrosshairYPosition);

	if (GetLookDirection(ScreenLocation, LookDirection, CameraWorldLocation)) {
		HitLocation = GetLookVectorHitLocation(LookDirection, CameraWorldLocation);
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& CameraWorldLocation) const
{	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

FVector ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector CameraWorldLocation) const
{
	FVector HitLocation = FVector(0);

	FHitResult OutHit;
	FVector Start, End;
	ECollisionChannel TraceChannel;

	Start = CameraWorldLocation;
	End = Start + LookDirection * LineTraceRange;
	TraceChannel = ECC_Visibility;

	bool bIsAHit;
	bIsAHit = GetWorld()->LineTraceSingleByChannel
	(
		OutHit,
		Start,
		End,
		TraceChannel
	);

	if (bIsAHit) {
		HitLocation = OutHit.Location;
	}

	return HitLocation;
}