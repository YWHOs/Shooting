// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = "Update Player Location Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &_ownerComp, uint8 *_nodeMemory, float _deltaSeconds)
{
    Super::TickNode(_ownerComp, _nodeMemory, _deltaSeconds);
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (playerPawn == nullptr)
    {
        return;
    }
    if(_ownerComp.GetAIOwner() == nullptr)
    {
        return;
    }
    if(_ownerComp.GetAIOwner() -> LineOfSightTo(playerPawn))
    {
        _ownerComp.GetBlackboardComponent() -> SetValueAsObject(GetSelectedBlackboardKey(), playerPawn);
    }
    else
    {
        _ownerComp.GetBlackboardComponent() -> ClearValue(GetSelectedBlackboardKey());
    }
}

