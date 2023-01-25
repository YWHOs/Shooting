// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AKillEmAllGameMode : public AShootingGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* _pawnKilled) override;

private:
	void EndGame(bool _isPlayerWinner);
};
