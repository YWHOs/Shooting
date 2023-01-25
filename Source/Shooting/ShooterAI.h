// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AShooterAI : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float _deltaSeconds) override;

	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	// float acceptanceRadius = 200;
};
