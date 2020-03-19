// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleGameMode.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "ConstructorHelpers.h"


AVehicleGameMode::AVehicleGameMode() 
{
	static ConstructorHelpers::FObjectFinder<USoundCue> CTSC(TEXT("/Game/Sound/CutDown/UI_Countdown_Cue.UI_Countdown_Cue"));
	CutTimeSoundCue = CTSC.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> BPSC(TEXT("/Game/Sound/CutDown/UI_CountdownFinish_Cue"));
	BeginPlaySoundCue = BPSC.Object;

	CountdownTime = 3;
}

void AVehicleGameMode::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AVehicleGameMode::Countdown, 1, true, 1);
}

void AVehicleGameMode::Countdown()
{

	UE_LOG(LogTemp, Warning, TEXT("%S"), *FString::SanitizeFloat(CountdownTime));
	if (CountdownTime == 0) 
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		if (CutTimeSoundCue != NULL) 
		{
			UGameplayStatics::PlaySoundAtLocation(this, CutTimeSoundCue, FVector(0, 0, 0));
		}
	}
	else 
	{
		if (BeginPlaySoundCue != NULL) 
		{
			UGameplayStatics::PlaySoundAtLocation(this, CutTimeSoundCue, FVector(0, 0, 0));
		}
		CountdownTime--;
	}
}
