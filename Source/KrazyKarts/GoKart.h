// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

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

USTRUCT()
struct FGoKartState {
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
		FGoKartMove LastMove;

	UPROPERTY()
		FVector Velocity;
	UPROPERTY()
		FTransform Transform;
};

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Replicated)
		FVector Velocity;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicatedTransform)
		FTransform ReplicatedTransform;
	UFUNCTION()
		void OnRep_ReplicatedTransform();


	void ApplyRotation(float DeltaTime);

	void UpdateLocationFromVelocity(float DeltaTime);

	FVector GetAirRessistance();
	FVector GetRollingRessistance();

	UPROPERTY(EditAnywhere)
		float Mass =1000;	//kg
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 10000;
	UPROPERTY(EditAnywhere)
		float MinTurningRadius= 10;
	UPROPERTY(EditAnywhere)
		float DragCoefficient= 16;//MaxDrivingForce/TopSpeed(m/s)
	UPROPERTY(EditAnywhere)
		float RollingRessistanceCoefficient = 0.015;

	UPROPERTY(Replicated)
		float Throttle;
	UPROPERTY(Replicated)
		float SteeringThrow;
	

	void MoveForward(float Value);
	void MoveRight(float Value);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_MoveForward(float Value);
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_MoveRight(float Value);
};
