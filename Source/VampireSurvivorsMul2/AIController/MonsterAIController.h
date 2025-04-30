// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController/StateAIController.h"
#include "Interface/DetectServiceInterface.h"
#include "AIState/MonsterState.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API AMonsterAIController : public AStateAIController, public IDetectServiceInterface
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void SetDetectedActor(AActor* NewDetectedActor) override;

private:
	void SetBlackBoardState(EMonsterState NewState);
};
