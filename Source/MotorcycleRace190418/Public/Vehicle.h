// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Vehicle.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USoundCue;
class UAudioComponent;
class UWheeledVehicleMovementComponent4W;
/**
 * 
 */
UCLASS()
class MOTORCYCLERACE190418_API AVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

protected:
	FVector InternalCameraOrigin;
	bool bInCarCameraActive;
	TArray<int32> GearSpeedArray;
	UWheeledVehicleMovementComponent4W* GVehicle4W;
	float FrontSteerAngle;
	bool bIsBrake = false;

	UPROPERTY(VisibleAnyWhere, Category = "CaemraComponent")
	UCameraComponent* ExternalCamera;

	UPROPERTY(VisibleAnyWhere, Category = "CaemraComponent")
	UCameraComponent* InternalCamera;

	UPROPERTY(VisibleAnyWhere, Category = "CaemraComponent")
	USceneComponent* InternalCameraBase;

	UPROPERTY(VisibleAnyWhere, Category = "CameraComponent")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundCue* EngineSound;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundCue* SteerSound;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
		UAudioComponent* SteerAudioComponent;
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	void OnHandBrakePressd();
	void OnHandBrakeRelesed();

	void OnToggleCamera();

	// …Ë÷√…˘“Ù
	virtual void BeginPlay() override;

	void PlayEngineSound();

	void OnSkid();

private:
	void SetDefaultMesh();
	void SetCameraInfo();
	void SetWheelInfo();

public:
	AVehicle();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
