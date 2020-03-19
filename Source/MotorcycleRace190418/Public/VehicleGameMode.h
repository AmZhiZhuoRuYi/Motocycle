// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VehicleGameMode.generated.h"



/**
 * 
 */
UCLASS()
class MOTORCYCLERACE190418_API AVehicleGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, Category="UI")
	int CountdownTime;
	FTimerHandle CountdownTimerHandle;

	USoundCue* CutTimeSoundCue;
	USoundCue* BeginPlaySoundCue;

	AVehicleGameMode();
	/* 进行倒计时 */ 
	void Countdown();
	

public:
	virtual void StartPlay() override;
	
};
