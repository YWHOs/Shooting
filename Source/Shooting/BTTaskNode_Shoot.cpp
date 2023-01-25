// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = "Shoot";
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent &_ownerComp, uint8 *_nodeMemory)
{
    Super::ExecuteTask(_ownerComp, _nodeMemory);

    if (_ownerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    AShooterCharacter* character = Cast<AShooterCharacter>(_ownerComp.GetAIOwner() -> GetPawn());
    if (character == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    character -> Shoot();

    return EBTNodeResult::Succeeded;
}
