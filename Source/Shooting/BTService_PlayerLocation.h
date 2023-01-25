// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UBTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent &_ownerComp, uint8 *_nodeMemory, float _deltaSeconds) override;

};
