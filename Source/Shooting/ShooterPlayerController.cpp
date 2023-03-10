// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD -> AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(class AActor *_endGameFocus, bool _isWinner)
{
    Super::GameHasEnded(_endGameFocus, _isWinner);

    HUD -> RemoveFromViewport();
    if (_isWinner)
    {
        UUserWidget* winScreen = CreateWidget(this, winScreenClass);
        if(winScreen != nullptr)
        {
            winScreen -> AddToViewport();
        }
    }
    else
    {
        UUserWidget* loseScreen = CreateWidget(this, loseScreenClass);
        if(loseScreen != nullptr)
        {
            loseScreen -> AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(restartTimer, this, &APlayerController::RestartLevel, restartDelay);
}

