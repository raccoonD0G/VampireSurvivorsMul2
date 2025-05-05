// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORSMUL2_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	int32 RedBoxCount = 0;
	int32 GreenBoxCount = 0;
	int32 BlueBoxCount = 0;

public:
	void AddRedBoxCount();

	void AddGreenBoxCount();

	void AddBlueBoxCount();

	void PauseGame();

public:
	void CheckAndSetWin();
	void SetLose();
};
