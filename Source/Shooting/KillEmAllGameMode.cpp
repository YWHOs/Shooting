// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAI.h"

void AKillEmAllGameMode::PawnKilled(APawn* _pawnKilled)
{
    Super::PawnKilled(_pawnKilled);

    APlayerController* playerController = Cast<APlayerController>(_pawnKilled -> GetController());
    if(playerController != nullptr)
    {
        EndGame(false);
    }
    for (AShooterAI* controller : TActorRange<AShooterAI>(GetWorld()))
    {
        if(!controller -> IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool _isPlayerWinner)
{
    for (AController* controller : TActorRange<AController>(GetWorld()))
    {
        bool isWinner = controller -> IsPlayerController() == _isPlayerWinner;
        controller -> GameHasEnded(controller -> GetPawn(), isWinner);
    }
}
