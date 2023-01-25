// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = "Update Player Location";
}
void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent &_ownerComp, uint8 *_nodeMemory, float _deltaSeconds)
{
    Super::TickNode(_ownerComp, _nodeMemory, _deltaSeconds);
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (playerPawn == nullptr)
    {
        return;
    }
    _ownerComp.GetBlackboardComponent() -> SetValueAsVector(GetSelectedBlackboardKey(), playerPawn -> GetActorLocation());
}

