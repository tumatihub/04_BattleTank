// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possessing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController possessing %s"), *ControlledTank->GetName())
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
