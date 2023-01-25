// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
void AShooterAI::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);


        GetBlackboardComponent() -> SetValueAsVector(TEXT("StartLocation"), GetPawn() -> GetActorLocation());

    }
}

void AShooterAI::Tick(float _deltaSeconds)
{
    Super::Tick(_deltaSeconds);

    // if(LineOfSightTo(playerPawn))
    // {
    //     SetFocus(playerPawn);
    //     MoveToActor(playerPawn, acceptanceRadius);
    // }
    // else
    // {
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     StopMovement();
    // }
}

bool AShooterAI::IsDead() const
{
    AShooterCharacter* controllerCharacter = Cast<AShooterCharacter>(GetPawn());
    if (controllerCharacter != nullptr)
    {
        return controllerCharacter -> IsDead();
    }
    return true;
}
