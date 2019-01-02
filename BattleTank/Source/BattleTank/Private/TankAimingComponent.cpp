// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet, float LaunchSpeed)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	bool bCanCalculateVelocity;
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Cast<USceneComponent>(Barrel)->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	// Calculate the OutLaunchVelocity
	bCanCalculateVelocity =  UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams(ECollisionResponse::ECR_Ignore),
		ActorsToIgnore,
		bDebug
	);
	if (bCanCalculateVelocity) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString())
}