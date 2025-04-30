// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/MonsterAIController.h"
#include "AIState/MonsterState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AI.h"

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AMonsterState* MonsterState = Cast<AMonsterState>(GetAIState());
	check(MonsterState);

	if (MonsterState)
	{
		MonsterState->OnStateChanged.AddUObject(this, &AMonsterAIController::SetBlackBoardState);
	}
}

void AMonsterAIController::SetDetectedActor(AActor* NewDetectedActor)
{
	AMonsterState* MonsterState = Cast<AMonsterState>(GetAIState());
	if (MonsterState)
	{
		MonsterState->SetCurrentState(EMonsterState::Chase);
	}
}


void AMonsterAIController::SetBlackBoardState(EMonsterState NewState)
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (BlackboardPtr)
	{
		BlackboardPtr->SetValueAsEnum(BBKEY_MONSTERSTATE, static_cast<uint8>(NewState));
	}
}