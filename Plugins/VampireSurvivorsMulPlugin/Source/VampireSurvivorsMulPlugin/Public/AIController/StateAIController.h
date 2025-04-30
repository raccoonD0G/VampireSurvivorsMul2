// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StateAIController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMULPLUGIN_API AStateAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AStateAIController();

protected:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* InPawn) override;

// BT Section
private:
	void RunAI();
	void StopAI();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBehaviorTree> BTAsset;

// State Section
public:
	class AAIState* GetAIState() const { return AIState; }

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAIState> AIStateClass;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class AAIState> AIState;

	
};
