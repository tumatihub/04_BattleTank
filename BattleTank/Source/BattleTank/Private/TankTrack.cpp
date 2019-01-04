// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"


void UTankTrack::SetThrottle(float Throttle)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	auto TrackName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Throttle: %f"), *TrackName, Throttle)
}

