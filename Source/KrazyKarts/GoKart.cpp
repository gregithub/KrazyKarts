// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKart.h"
#include "Components/InputComponent.h"
#include"Engine/World.h"

// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//*100 to cm

	FVector Force = GetActorForwardVector()* MaxDrivingForce * Throttle;
	Force += GetAirRessistance();
	Force += GetRollingRessistance();
	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * DeltaTime;

	ApplyRotation(DeltaTime);
	UpdateLocationFromVelocity(DeltaTime);
}
FVector AGoKart::GetAirRessistance() {
	return -Velocity.GetSafeNormal()* Velocity.SizeSquared() * DragCoefficient;
}
FVector AGoKart::GetRollingRessistance( ) {
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100;	//converting from UE units =9,81
	float NormalForce = Mass * AccelerationDueToGravity;
	return -Velocity.GetSafeNormal()* NormalForce * RollingRessistanceCoefficient;
}


void AGoKart::ApplyRotation(float DeltaTime)
{
	float DeltaLocation = FVector::DotProduct(GetActorForwardVector(),Velocity) * DeltaTime;
	float RotationAngle = DeltaLocation / MinTurningRadius * SteeringThrow;
	FQuat RotationDelta(GetActorUpVector(), RotationAngle);

	Velocity = RotationDelta.RotateVector(Velocity);
	AddActorWorldRotation(RotationDelta);
}

void AGoKart::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;

	FHitResult Hit;
	
	AddActorWorldOffset(Translation, true, &Hit);
	if (Hit.IsValidBlockingHit()) {
		Velocity = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);

}

void  AGoKart::MoveForward(float Value){
	Throttle = Value;
}

void  AGoKart::MoveRight(float Value) {
	SteeringThrow = Value;
}