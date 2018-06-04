// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrell.h"
#include "Projectile.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

}

void ATank::Fire()
{
	
	bool isReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTime);

	if (Barrell && isReloaded) {

		LastFireTime = FPlatformTime::Seconds();
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, Barrell->GetSocketLocation(FName("Projectile")), Barrell->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) {	return;}
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s"),*GetName(), *HitLocation.ToString());

}

