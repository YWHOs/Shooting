// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(class AActor *_endGameFocus = nullptr, bool _isWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> loseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> winScreenClass;

	UPROPERTY(EditAnywhere)
	float restartDelay = 5;

	FTimerHandle restartTimer;

	UUserWidget* HUD;
};
