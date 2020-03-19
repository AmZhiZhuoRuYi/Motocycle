// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Vehicle.h"
#include "Camera/CameraComponent.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Public/FrontVehicleWheel.h"
#include "Public/RealVehicleWheel.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

AVehicle::AVehicle()
{
	bInCarCameraActive = false;
	SetDefaultMesh();
	SetCameraInfo();
	SetWheelInfo();
}

void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	if (EngineSound->IsValidLowLevelFast()) 
	{
		EngineSound->PitchMultiplier = 0.2f;
		AudioComponent->SetSound(EngineSound);
	}

	if (SteerSound->IsValidLowLevelFast()) 
	{
		SteerAudioComponent->SetSound(SteerSound);
	}
	
}

void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OnSkid();
}

void AVehicle::SetDefaultMesh()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarMesh(TEXT("/Game/Car/mclaren/mclaren.mclaren"));
	GetMesh()->SetSkeletalMesh(CarMesh.Object);
}

void AVehicle::SetCameraInfo()
{
	InternalCameraOrigin = FVector(8.0f, -30.0f, 25.0f);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprinArm"));
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0, 0));
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 750.0f;
	SpringArm->SetupAttachment(RootComponent);


	ExternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ExternalCamera"));
	ExternalCamera->SetupAttachment(SpringArm);

	InternalCameraBase = CreateDefaultSubobject<USceneComponent>(TEXT("InternalCameraBase"));
	InternalCameraBase->SetupAttachment(GetMesh());
	InternalCameraBase->SetRelativeLocation(InternalCameraOrigin);

	InternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("InternalCamera"));
	InternalCamera->SetupAttachment(InternalCameraBase);
}

void AVehicle::SetWheelInfo()
{
	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());
	check(Vehicle4W->WheelSetups.Num() == 4);

	Vehicle4W->WheelSetups[0].WheelClass = UFrontVehicleWheel::StaticClass();
	Vehicle4W->WheelSetups[0].BoneName = FName("right_front_bone");

	Vehicle4W->WheelSetups[1].WheelClass = UFrontVehicleWheel::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("left_front_bone");

	Vehicle4W->WheelSetups[2].WheelClass = URealVehicleWheel::StaticClass();
	Vehicle4W->WheelSetups[2].BoneName = FName("right_rear_bone");

	Vehicle4W->WheelSetups[3].WheelClass = URealVehicleWheel::StaticClass();
	Vehicle4W->WheelSetups[3].BoneName = FName("left_rear_bone");

	GVehicle4W = Vehicle4W;
	GearSpeedArray = { 0, 18, 43, 63, 120, 151 };

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComponent->SetupAttachment(RootComponent);

	SteerAudioComponent = CreateAbstractDefaultSubobject<UAudioComponent>(TEXT("SteerAudioComp"));
	SteerAudioComponent->SetupAttachment(RootComponent);
	

}

void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVehicle::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVehicle::MoveRight);
	PlayerInputComponent->BindAction("HandBrake", IE_Pressed, this, &AVehicle::OnHandBrakePressd);
	PlayerInputComponent->BindAction("HandBrake", IE_Released, this, &AVehicle::OnHandBrakeRelesed);

	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &AVehicle::OnToggleCamera);
}

void AVehicle::MoveForward(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
	PlayEngineSound();
}

void AVehicle::MoveRight(float Value)
{
	FrontSteerAngle = Value;
	GetVehicleMovementComponent()->SetSteeringInput(Value);
}

void AVehicle::OnHandBrakePressd()
{
	bIsBrake = true;
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AVehicle::OnHandBrakeRelesed()
{
	bIsBrake = false;
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AVehicle::OnToggleCamera()
{
	if (bInCarCameraActive)
	{
		ExternalCamera->Activate();
		InternalCamera->Deactivate();
		bInCarCameraActive = false;
	}
	else
	{
		InternalCamera->Activate();
		ExternalCamera->Deactivate();
		bInCarCameraActive = true;
	}
}

void AVehicle::PlayEngineSound()
{
	int tIndex;
	for (int i = 0; i < GearSpeedArray.Num() - 2; i++) 
	{
		if (GetVehicleMovement()->GetForwardSpeed() * 0.036f >= GearSpeedArray[i]) 
		{
			tIndex = i;
			break;
		}
	}

	int tMinSpeed = GearSpeedArray[tIndex];
	int tMaxSpeed = GearSpeedArray[tIndex + 1];

	EngineSound->PitchMultiplier = 0.1f + FMath::Abs(GetVehicleMovement()->GetForwardSpeed() * 0.036f - tMinSpeed) / (tMaxSpeed - tMinSpeed);

	if (!AudioComponent->IsPlaying()) 
	{
		AudioComponent->Play();
	}
}

void AVehicle::OnSkid()
{
	if (GetVehicleMovement()->GetForwardSpeed() * 0.036f > 40 && FMath::Abs(FrontSteerAngle) > 0.8f
		|| GetVehicleMovement()->GetForwardSpeed() * 0.036f	> 20 && bIsBrake) 
	{
		SteerAudioComponent->Play();
		//UE_LOG(LogTemp, Warning, TEXT("OnSkid"));
	}
}

