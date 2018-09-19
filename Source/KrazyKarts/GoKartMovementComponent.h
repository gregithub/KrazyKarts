// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
		float DeltaTime;
	UPROPERTY()
		float Time;

	UPROPERTY()
		float Throttle;
	UPROPERTY()
		float SteeringThrow;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SimulateMove(const FGoKartMove& Move);
	
	void SetVelocity(FVector Val) { Velocity = Val; };
	FVector GetVelocity() { return Velocity; };

	void SetThrottle(float Val) { Throttle = Val; };
	void SetSteeringThrow(float Val) { SteeringThrow = Val; };

	FGoKartMove GetLastMove() { return LastMove; };

private:
	FGoKartMove CreateMove(float DeltaTime);

	
	void ApplyRotation(float DeltaTime, float SteeringThrow);
	void UpdateLocationFromVelocity(float DeltaTime);

	FVector GetAirRessistance();
	FVector GetRollingRessistance();

	FVector Velocity;

	UPROPERTY(EditAnywhere)
		float Mass = 1000;	//kg
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;
	UPROPERTY(EditAnywhere)
		float MinTurningRadius = 10;
	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16;//MaxDrivingForce/TopSpeed(m/s)
	UPROPERTY(EditAnywhere)
		float RollingRessistanceCoefficient = 0.015;

	float Throttle;
	float SteeringThrow;	

	FGoKartMove LastMove;
};
